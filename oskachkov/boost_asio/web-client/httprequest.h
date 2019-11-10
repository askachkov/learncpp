#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <string>
#include <istream>
#include <ostream>
#include <map>

namespace http
{

typedef std::string String;

class Header
{
    String host;
    String userAgent;
    String accept;
    String acceptLanguage;
    String acceptEncoding;
    String contentType;
    String contentLength;
    String connection;
    String pragma;
    String cacheControl;
};

std::istream& operator >> (std::istream& s, HeaderRow & value);
std::ostream& operator << (std::ostream& s, const HeaderRow & value);

}

#endif // HTTPREQUEST_H
