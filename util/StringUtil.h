#ifndef BASE_TOOL_STRING_UTIL_H__
#define BASE_TOOL_STRING_UTIL_H_

#include <stdio.h>
#include <ctype.h>
#include <algorithm>
#include <string>
#include <vector>

namespace basetool {

     // type to string
    std::string toString( int value );
    std::string toString( long value );
    std::string toString( long long value );
    std::string toString( unsigned value );
    std::string toString( unsigned long value );
    std::string toString( unsigned long long value );
    std::string toString( float value );
    std::string toString( double value );
    std::string toString( long double value );

    // string util
    void strSplit(const std::string & str, const std::string & div_str, std::vector<std::string> & value);
    std::string strJoin(const std::vector<std::string> & vl, const std::string & connect_str);
    std::string strJoinSides(const std::vector<std::string> & vl, const std::string &left_str,
            const std::string & right_str, const std::string & connect_str);
    void strUnique(std::vector<std::string> & ve);
    void strToUpper(std::string & str);
    void strToLower(std::string & str);
    void strTrim(std::string & str);

} //namespace basetool

#endif //BASE_TOOL_STRING_UTIL_H_
