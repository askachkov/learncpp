#include <iostream>
#include "variant.h"
#include <sstream>
#include <list>
#include <cstdio>

#include "serializer.h"
#include "json.h"

using namespace std;

struct Example
{
    int age;
    string name;
    string ids[3];
};

template <>
Variant serialize<Example>(const Example & data)
{
    VariantObject res;
    res.push_back( {"age", serialize(data.age)} );
    res.push_back( {"name", serialize(data.name)} );
    res.push_back( {"ids", serializeArray(data.ids)} );
    return Variant(res);
}

std::string toJson(const Variant & v)
{
    using namespace json;
    ostringstream oss;
    writeToStream(oss, v);
    return oss.str();
}

int main()
{


    //foo(int(5));

    Example e = {356, "Alex", {"00-Fx", "01-Fx", "02-Fx"}};
    Variant v = serialize(e);

    cout << toJson(v);

    return 0;
}

