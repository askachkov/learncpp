#include "test.h"
#include "serializers_b.h"
#include <iostream>
#include <map>
#include <boost/type_traits/integral_constant.hpp>
#include <cstddef> // size_t

struct my_other_struct
{
    int my_other_integer;
};

struct my_struct
{
    int my_integer;

    typedef int my_array_t[2];
    my_array_t my_array;

    typedef my_other_struct my_other_structs_t[3];
    my_other_structs_t my_other_structs;

    typedef std::map<int, int> map_v;
    map_v m;
};

BOOST_FUSION_ADAPT_STRUCT(
        my_struct,
        (int, my_integer)
        (my_struct::my_array_t, my_array)
        (my_struct::my_other_structs_t, my_other_structs)
        //(auto, m)
        )
BOOST_FUSION_ADAPT_STRUCT(my_other_struct, (int, my_other_integer))


#define GENERATE_HAS_MEMBER(member)                                               \
                                                                                  \
template < class T >                                                              \
class HasMember_##member                                                          \
{                                                                                 \
private:                                                                          \
    using Yes = char[2];                                                          \
    using  No = char[1];                                                          \
                                                                                  \
    struct Fallback { int member; };                                              \
    struct Derived : T, Fallback { };                                             \
                                                                                  \
    template < class U >                                                          \
    static No& test ( decltype(U::member)* );                                     \
    template < typename U >                                                       \
    static Yes& test ( U* );                                                      \
                                                                                  \
public:                                                                           \
    static const bool RESULT = sizeof(test<Derived>(nullptr)) == sizeof(Yes); \
};                                                                                \
                                                                                  \
template < class T >                                                              \
struct has_member_##member                                                        \
: public std::integral_constant<bool, HasMember_##member<T>::RESULT>              \
{                                                                                 \
};

struct V
{

};

GENERATE_HAS_MEMBER(begin)

void Test::test2()
{
    using namespace std;
    map<int, int> m;
    V v;

    cout << has_member_begin< map<int, int> >::value << endl;
    cout << has_member_begin< V >::value << endl;

}

