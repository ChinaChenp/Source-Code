#ifndef BASE_TOOL_STRING_UTIL_H__
#define BASE_TOOL_STRING_UTIL_H_

#include <stdio.h>
#include <ctype.h>
#include <algorithm>
#include <string>
#include <vector>

namespace basetool {
    using std::string;
    using std::vector;

     //to string
    string toString( int value );
    string toString( long value );
    string toString( long long value );
    string toString( unsigned value );
    string toString( unsigned long value );
    string toString( unsigned long long value );
    string toString( float value );
    string toString( double value );
    string toString( long double value );

    void strSplit(const string & str, const string & div_str, vector<string> & value);
    string strJoin(const vector<string> vl, const string & connect_str);
    void strUnique(vector<string> & ve);
    void strToUpper(string & str);
    void strToLower(string & str);
    void strTrim(string & str);

} //namespace basetool

#endif //BASE_TOOL_STRING_UTIL_H_
