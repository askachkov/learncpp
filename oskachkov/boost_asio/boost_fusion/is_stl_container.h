#ifndef IS_STL_CONTAINER
#define IS_STL_CONTAINER

#include <boost/type_traits/integral_constant.hpp>
#include <cstddef> // size_t

namespace boost {

#if defined( __CODEGEARC__ )
   template <class T> struct is_array : public integral_constant<bool, __is_array(T)> {};
#else
   template <class T> struct is_array : public false_type {};
#if !defined(BOOST_NO_ARRAY_TYPE_SPECIALIZATIONS)
   template <class T, std::size_t N> struct is_array<T[N]> : public true_type {};
   template <class T, std::size_t N> struct is_array<T const[N]> : public true_type{};
   template <class T, std::size_t N> struct is_array<T volatile[N]> : public true_type{};
   template <class T, std::size_t N> struct is_array<T const volatile[N]> : public true_type{};
#if !BOOST_WORKAROUND(__BORLANDC__, < 0x600) && !defined(__IBMCPP__) &&  !BOOST_WORKAROUND(__DMC__, BOOST_TESTED_AT(0x840))
   template <class T> struct is_array<T[]> : public true_type{};
   template <class T> struct is_array<T const[]> : public true_type{};
   template <class T> struct is_array<T const volatile[]> : public true_type{};
   template <class T> struct is_array<T volatile[]> : public true_type{};
#endif
#endif

#endif

} // namespace boost

#endif // IS_STL_CONTAINER

