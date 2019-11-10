#include "json.h"

namespace json {

using namespace std;

static bool readstring(istream & in, Variant & node)
{
    string res;
    char c;
    in.ignore();//skip front "
    while ( (in.peek() != '"' || c == '\\') && in >> c ) {
        res.push_back(c);
    }
    in.ignore();//skip rear"
    node = res;
    return true;
}

static bool readNull(istream & in, Variant & node)
{
    static const string nn = "null";
    char buf[5] = {0};
    while ( in.read(buf, 4) ) {
        if ( nn == buf ){
            node = nullptr;
            return true;
        }
    }
    in.setstate(ios_base::failbit);
    return false;
}

static bool readTrue(istream & in, Variant & node)
{
    static const string nn = "true";
    char buf[5] = {0};
    while ( in.read(buf, 4) ) {
        if ( nn == buf ){
            node = true;
            return true;
        }
    }
    in.setstate(ios_base::failbit);
    return false;
}

static bool readFalse(istream & in, Variant & node)
{
    static const string nn = "false";
    char buf[6] = {0};
    while ( in.read(buf, 5) ) {
        if ( nn == buf ){
            node = false;
            return true;
        }
    }
    in.setstate(ios_base::failbit);
    return false;
}

static bool readNumber(istream & in, Variant & node)
{
    double res = 0;
    if ( in >> res ){
        node = res;
    }
    return true;
}

static bool readVariant(istream & stream, Variant & node);

static bool readArray(istream & in, Variant & node)
{
    VariantArray res;
    Variant buf;
    char ch;
    in.ignore();//skip front '['
    while ( readVariant(in, buf) && (in >> std::ws >> ch) ){
        res.push_back(buf);
        switch ( ch ){
            case ',': {
            } break;
            case ']': 
                node = res;
                return true;
            default: {
                in.setstate(std::ios_base::failbit);
                return false;
            }
        }
    }
    if (in >> ch && ch == ']'){
		node = res;
		return true;
    }
    in.setstate(std::ios_base::failbit);
    return false;
}

static bool readObject(istream & in, Variant & node)
{
    VariantObject res;
    Variant key;
    Variant val;
    char ch;
    
    in.ignore();//skip front '{'
    do {
        in >> ws;
        if ( in.peek() == '}' ){
        	node = res;
        	return true;
        }
        if ( !readstring(in, key) ||
             !(in >> ws >> ch) || (ch != ':') ||
             !readVariant(in, val) ||
             !(in >> std::ws >> ch) ) {
            return false;
        }
        res.push_back({key.castTo<string>(), val});
        switch ( ch ){
            case ',': {
            } break;
            case '}': 
                node = res;
                return true;
            default: {
                in.setstate(std::ios_base::failbit);
                return false;
            }
        }
    } while (true);
    return true;
}

static bool readVariant(istream & stream, Variant & node)
{
    switch ( (stream >> std::ws).peek() ){
        case '"': return readstring(stream, node);
        case '{': return readObject(stream, node);
        case '}': return false;
        case ']': return false;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9': return readNumber(stream, node);
        case '[': return readArray(stream, node);
        case 'n': return readNull(stream, node);
        case 't': return readTrue(stream, node);
        case 'f': return readFalse(stream, node);
        default: {
            stream.setstate(std::ios_base::failbit);
        }
    }
    return false;
}

ostream & writeTabs(ostream & os, int tabs)
{
	os << "\n";
	for ( int i = 0; i < tabs; ++i ){
		os << "  ";
	}
	return os;
}

static void writeVariant(ostream & os, const Variant & node, int tabs);

static void writeObject(ostream & os, const Variant & node, int tabs)
{
	os << "{";
    VariantObject no = node.castTo<VariantObject>();
	for ( size_t i = 0; i < no.size(); ++i ){
		if ( i > 0 )
			os << ",";
		writeTabs(os, tabs+1);
        os << "\"" << no[i].name << "\": ";
        writeVariant(os, no[i].value, tabs+1);
	}
	writeTabs(os, tabs) << "}";
}

static void writeArray(ostream & os, const Variant & node, int tabs)
{
	os << "[";
    VariantArray no = node.castTo<VariantArray>();
	for ( size_t i = 0; i < no.size(); ++i ){
		if ( i > 0 )
			os << ",";
		writeTabs(os, tabs+2);
		writeVariant(os, no[i], tabs+2);
	}
	writeTabs(os, tabs+1) << "]";
}

static void writeVariant(ostream & os, const Variant & node, int tabs)
{
    if ( node.isNumber() ){
        os << node;
    }
    if ( node.typeIs<bool>() ){
        os << (node.castTo<bool>() ? "true" : "false");
    }
    if ( node.isNull() ){
        os << "null";
    }
    if ( node.typeIs<std::string>() ){
        os << "\"" << node << "\"";
    }
    if ( node.isArray() ){
        writeArray(os, node, tabs);
    }
    if ( node.isObject() ){
        writeObject(os, node, tabs);
    }
}

void writeToStream(ostream &stream, const Variant &node)
{
    writeVariant(stream, node, 0);
}

void readFromStream(istream &stream, Variant &node)
{
    readVariant(stream, node);
}

}
