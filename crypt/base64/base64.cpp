//
// Author: Ping Chen
// Date: 2017.04.06
//

#include "base64.h"

namespace base64 {
using std::string;

namespace detail {
static const string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

static inline bool is_base64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}
} // namespace detail

string base64_encode(const char * encode_bytes, unsigned int bytes_len) {
    string ret;
    int i = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (bytes_len--) {
        char_array_3[i++] = *(encode_bytes++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; (i <4) ; i++) {
                ret += detail::base64_chars[char_array_4[i]];
            }
            i = 0;
        }
    }

    int j = 0;
    if (i) {
        for (j = i; j < 3; j++) {
            char_array_3[j] = '\0';
        }

        char_array_4[0] = ( char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] =   char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++) {
            ret += detail::base64_chars[char_array_4[j]];
        }

        while ((i++ < 3)) {
            ret += '=';
        }
    }

    return ret;
}

string base64_encode(const string & encode_str) {
    return base64_encode(encode_str.c_str(), encode_str.size());
}

string base64_decode(const char *decode_bytes, unsigned int bytes_len) {
    int i = 0;
    int in = 0;
    unsigned char char_array_4[4], char_array_3[3];
    string ret;

    while (bytes_len-- && (decode_bytes[in] != '=') && detail::is_base64(decode_bytes[in])) {
        char_array_4[i++] = decode_bytes[in++];
        if (i == 4) {
            for (i = 0; i <4; i++) {
                char_array_4[i] = detail::base64_chars.find(char_array_4[i]);
            }

            char_array_3[0] = ( char_array_4[0] << 2       ) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) +   char_array_4[3];

            for (i = 0; (i < 3); i++) {
                ret += char_array_3[i];
            }
            i = 0;
        }
    }

    int j = 0;
    if (i) {
        for (j = i; j <4; j++) {
            char_array_4[j] = 0;
        }

        for (j = 0; j <4; j++) {
            char_array_4[j] = detail::base64_chars.find(char_array_4[j]);
        }

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; (j < i - 1); j++) {
            ret += char_array_3[j];
        }
    }

    return ret;
}

string base64_decode(const string & decode_str) {
    return base64_decode(decode_str.c_str(), decode_str.size());
}

} // namespace base64
