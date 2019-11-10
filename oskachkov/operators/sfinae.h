#ifndef SFINAE
#define SFINAE

#include <iostream>

template<class T, class U, class V>
struct has_ostream_shift
{
  template<class T1,
           class Reference = decltype(
             (*std::declval<std::ostream*>()) << (*std::declval<T*>())
           ),
           class = typename std::enable_if<
             !std::is_void<Reference>::value
           >::type>
  static U test(int);

  template<class>
  static V test(...);

  using type = decltype(test<T>(0));
};

// cout << has_ostream_shift<int>::value  << endl;

#endif // SFINAE

