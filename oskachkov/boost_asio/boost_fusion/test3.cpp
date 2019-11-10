#include "test.h"
#include <sstream>
#include <map>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

void example() {
    // Write json.
    ptree pt;
    pt.put ("foo", "bar");
    std::ostringstream buf;
    write_json (buf, pt, false);
    std::string json = buf.str(); // {"foo":"bar"}
    std::cout << "Json:" << json << std::endl;

            // Read json.
            ptree pt2;
    std::istringstream is (json);
    read_json (is, pt2);
    std::string foo = pt2.get<std::string> ("foo");
    std::cout << "Property:" << foo << std::endl;
}

std::string map2json (const std::map<std::string, std::string>& map) {
    ptree pt;
    for (auto& entry: map)
        pt.put (entry.first, entry.second);
    std::ostringstream buf;
    write_json (buf, pt, false);
    return buf.str();
}

void Test::test3()
{
    example();
}

