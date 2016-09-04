#ifndef COMMON_URLCODEC_H_
#define COMMON_URLCODEC_H_

#include <string>
#include <sstream>

namespace basetool {

inline unsigned char to_hex( unsigned char x) {
    return x + (x > 9 ? ('A'-10) : '0');
}

inline unsigned char from_hex (unsigned char ch) {
    if (ch <= '9' && ch >= '0')
        ch -= '0';
    else if (ch <= 'f' && ch >= 'a')
        ch -= 'a' - 10;
    else if (ch <= 'F' && ch >= 'A')
        ch -= 'A' - 10;
    else
        ch = 0;
    return ch;
}

std::string UrlDecode(const std::string & url);
std::string UrlEncode(const std::string & url);
}
#endif //COMMON_URLCODEC_H_
