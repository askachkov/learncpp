#ifndef JSON_H
#define JSON_H

//#include "node.h"
#include <variant.h>
#include <iostream>

namespace json {
    void writeToStream(std::ostream& stream, const Variant & node);
    void readFromStream(std::istream& stream, Variant & node);
}

#endif
