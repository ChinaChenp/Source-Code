#include "StringUtil.h"

namespace basetool {
    string toString( int value ) {
        char buf[64] = {0};
        snprintf(buf, 64, "%d", value);
        return buf;
    }

    string toString( long value ) {
        char buf[64] = {0};
        snprintf(buf, 64, "%ld", value);
        return buf;
    }

    string toString( long long value ) {
        char buf[64] = {0};
        snprintf(buf, 64, "%lld", value);
        return buf;
    }

    string toString( unsigned value ) {
        char buf[64] = {0};
        snprintf(buf, 64, "%u", value);
        return buf;
    }

    string toString( unsigned long value ) {
        char buf[64] = {0};
        snprintf(buf, 64, "%lu", value);
        return buf;
    }

    string toString( unsigned long long value ) {
        char buf[64] = {0};
        snprintf(buf, 64, "%llu", value);
        return buf;
    }

    string toString( float value ) {
        char buf[64] = {0};
        snprintf(buf, 64, "%f", value);
        return buf;
    }

    string toString( double value ){
        char buf[64] = {0};
        snprintf(buf, 64, "%f", value);
        return buf;
    }

    string toString( long double value ){
        char buf[64] = {0};
        snprintf(buf, 64, "%Lf", value);
        return buf;
    }

    void strSplit(const string & str, const string & div_str, vector<std::string> & value) {
        int size = str.size();
        std::string::size_type pos;
        for (int i = 0; i < size;) {
            pos = str.find(div_str, i);
            value.push_back(str.substr(i, pos-i));

            if (pos == std::string::npos) {
                break;
            } else {
                i = pos + div_str.size();
            }
        }
        return;
    }

    std::string strJoin(const std::vector<std::string> vl, const string & connect_str) {
        string result;

        int size = vl.size();
        for (int i=0; i< size; ++i) {
            if (i+1 == size) {
                result += vl[i];
            } else {
                result += vl[i] + connect_str;
            }
        }
        return result;
    }

    void strUnique(std::vector<std::string> & vl) {
        sort(vl.begin(), vl.end());
        vl.erase(unique(vl.begin(), vl.end()), vl.end());
    }

    void strToUpper(std::string & str) {
        std::string::iterator it = str.begin();
        for (; it != str.end(); ++it) {
            *it = toupper(*it);
        }
    }

    void strToLower(std::string & str) {
        std::string::iterator it = str.begin();
        for (; it != str.end(); ++it) {
            *it = tolower(*it);
        }
    }

    void strTrim(std::string & str) {
        string::size_type begin = 0, end = 0;
        const char *s = str.c_str();

        while(*s++ == ' ') {
            ++begin;
        }
        s = str.c_str();

        end = str.size() - 1;
        while(end > begin && s[end] == ' ') {
             end--;
        }

        str = str.substr(begin, end - begin + 1);
    }
}
