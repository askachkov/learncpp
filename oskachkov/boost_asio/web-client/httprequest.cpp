#include "httprequest.h"
#include <map>

namespace http {

#define SAFE_HEADER_FILL(FIELD) if ( m.find(#FIELD) != m.end() ){ value.FIELD = m[#FIELD]; }

std::istream &http::operator >>(std::istream &s, Header &value)
{
    using namespace std;
    std::map<String, String> m;
    std::pair<String, String> p;
    if ( !isspace(s.peek()) && getline(s, p.first, ':')){
        if (getline(s, p.second)){
            m.insert(p);
        }
    }
    SAFE_HEADER_FILL(host);
    SAFE_HEADER_FILL(userAgent);
    SAFE_HEADER_FILL(accept);
    SAFE_HEADER_FILL(acceptLanguage);
    SAFE_HEADER_FILL(acceptEncoding);
    SAFE_HEADER_FILL(contentType);
    SAFE_HEADER_FILL(contentLength);
    SAFE_HEADER_FILL(connection);
    SAFE_HEADER_FILL(pragma);
    SAFE_HEADER_FILL(cacheControl);
    return s;
}

std::ostream &http::operator <<(std::ostream &s, const http::HeaderRow &value)
{
    return s << value.key << ": " << value.value << "\n";
}

}


