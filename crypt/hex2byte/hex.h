//
// Author: Ping Chen
// Date: 2017.04.06
//

#ifndef HEX_H_
#define HEX_H_

#include <ctype.h>
#include <string>

namespace hexcodec {

std::string bytes2hex(const std::string & msg) {
    std::string hex_str;
    hex_str.reserve(msg.size() * 2);

    const char *HexCode = "0123456789ABCDEF";
    for (size_t i = 0; i < msg.size(); ++i) {
        hex_str += HexCode[(::toupper(msg[i]) & 0xF0) >> 4];
        hex_str += HexCode[(::toupper(msg[i]) & 0x0F)];
    }
    return hex_str;
}

std::string hex2bytes(const std::string & msg) {
    std::string bytes_str;
    bytes_str.reserve(msg.size() / 2);

    for (size_t i = 0; i < msg.size(); i += 2) {
        char bit = ::toupper(msg[i]);
        char left = bit >= 'A' ? bit - 'A' + 10 : bit - '0';

        bit = ::toupper(msg[i + 1]);
        char right = bit >= 'A' ? bit - 'A' + 10 : bit - '0';

        bytes_str += (left << 4) | right;
    }
    return bytes_str;
}

} // namespace hexcodec

#endif // HEX_H_
