#ifndef BASE_TOOL_STRING_UTIL_H_
#define BASE_TOOL_STRING_UTIL_H_

#include <stdio.h>
#include <ctype.h>
#include <algorithm>
#include <string>
#include <vector>

namespace basetool {

     // type to string
    std::string to_str( int value );
    std::string to_str( long value );
    std::string to_str( long long value );
    std::string to_str( unsigned value );
    std::string to_str( unsigned long value );
    std::string to_str( unsigned long long value );
    std::string to_str( float value );
    std::string to_str( double value );
    std::string to_str( long double value );

    // string util
    void str_split(const std::string & str, const std::string & div_str, std::vector<std::string> & value);
    std::string str_join(const std::vector<std::string> & vl, const std::string & connect_str);
    std::string str_join_sides(const std::vector<std::string> & vl, const std::string &left_str,
            const std::string & right_str, const std::string & connect_str);
    void str_unique(std::vector<std::string> & ve);
    void str_toupper(std::string & str);
    void str_tolower(std::string & str);
    void str_trim(std::string & str);

    std::string::size_type find_str_npos(const std::string & source, const std::string & target,
            unsigned int count = 1);

} //namespace basetool

#endif //BASE_TOOL_STRING_UTIL_H_
