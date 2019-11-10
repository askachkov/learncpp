#ifndef SFINEA
#define SFINEA

template<class T, class U, class V>
struct has_ostream_shift
{
  template<class T1,
           class Reference = decltype(
             (*std::declval<std::ostream*>()).beging()
           )>
  static U test(int);

  template<class>
  static V test(...);

  using type = decltype(test<T>(0));
};

#endif // SFINEA

