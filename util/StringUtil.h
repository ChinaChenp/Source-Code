#define BASE_TOOL_STRING_UTIL_H__
#define BASE_TOOL_STRING_UTIL_H_

#include <stdio.h>
#include <algorithm>
#include <string>

namespace basetool {

     //to string
    std::string toString( int value ) {
        char buf[64] = {0};
        snprintf(buf, 64, "%d", value);
        return buf;
    }

    std::string toString( long value ) {
        char buf[64] = {0};
        snprintf(buf, 64, "%ld", value);
        return buf;
    }

    std::string toString( long long value ) {
        char buf[64] = {0};
        snprintf(buf, 64, "%lld", value);
        return buf;
    }

    std::string toString( unsigned value ) {
        char buf[64] = {0};
        snprintf(buf, 64, "%u", value);
        return buf;
    }

    std::string toString( unsigned long value ) {
        char buf[64] = {0};
        snprintf(buf, 64, "%lu", value);
        return buf;
    }

    std::string toString( unsigned long long value ) {
        char buf[64] = {0};
        snprintf(buf, 64, "%llu", value);
        return buf;
    }
    std::string toString( float value ) {
        char buf[64] = {0};
        snprintf(buf, 64, "%f", value);
        return buf;
    }

    std::string toString( double value ){
        char buf[64] = {0};
        snprintf(buf, 64, "%f", value);
        return buf;
    }

    std::string toString( long double value ){
        char buf[64] = {0};
        snprintf(buf, 64, "%Lf", value);
        return buf;
    }

    void strSplit(const string & str, const string & div_str, vector<std::string> value);
    std::string strJoin(const std::vector<std::string> vl, const string & connect_str);

} //namespace basetool

#endif //BASE_TOOL_STRING_UTIL_H_
