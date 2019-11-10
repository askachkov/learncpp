#include <iostream>
#include <cstdarg>
#include "shared_ptr.h"
#include "unique_ptr.h"
#include "variant.h"
#include <map>
#include <string>

using namespace std;
template < class T >
class HasMember_begin
{
private:
    using Yes = char[2];
    using  No = char[1];

    struct Fallback { int begin; };
    struct Derived : T, Fallback { };

    template < class U >
    static No& test ( decltype(U::begin)* );
    template < typename U >
    static Yes& test ( U* );

public:
    static const bool RESULT = sizeof(test<Derived>(nullptr)) == sizeof(Yes);
};

template < class T >
struct has_member_begin
: public std::integral_constant<bool, HasMember_begin<T>::RESULT>
{
};


int main()
{


    cout << has_member_begin<map<int,int>>::value << endl;
    cout << has_member_begin<has_member_begin<int>>::value << endl;
    return 0;
}

