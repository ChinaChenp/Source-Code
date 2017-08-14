// Url encode and decode.
// RFC3986 https://tools.ietf.org/html/rfc3986
// author : chenping0114@autohome.com.cn
// date : 2015-12-12

#include "UrlCodec.h"

namespace basetool {

std::string UrlEncode(const std::string & s) {
    std::ostringstream os;

    for ( std::string::const_iterator ci = s.begin(); ci != s.end(); ++ci ) {
        if ((*ci >= 'a' && *ci <= 'z') ||
           (*ci >= 'A' && *ci <= 'Z') ||
           (*ci >= '0' && *ci <= '9') ||
           (*ci == '-' || *ci == '_' || *ci == '.' || *ci == '~')) {
            // allowed
            os << *ci;
        } else if ( *ci == ' ' ) { //java or php
            os << '+';
        } else {
            os << '%' << to_hex(*ci >> 4) << to_hex(*ci % 16);
        }
    }
    return os.str();
}

std::string UrlDecode (const std::string & str) {
    std::string result;
    std::string::size_type i;
    for (i = 0; i < str.size(); ++i) {
        if (str[i] == '+') {
            result += ' ';
        } else if (str[i] == '%' && str.size() > i + 2 &&
            isxdigit(str[i+1]) && isxdigit(str[i+2])) {
            const unsigned char ch1 = from_hex(str[i + 1]);
            const unsigned char ch2 = from_hex(str[i + 2]);
            const unsigned char ch = (ch1 << 4) | ch2;
            result += ch;
            i += 2;
        } else {
            result += str[i];
        }
    }
    return result;
}
} //namespace basetool
