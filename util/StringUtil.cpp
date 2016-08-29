#include "StringUtil.h"

namespace basetool {
    using std::string;
    using std::vector;

    string to_str( int value ) {
        char buf[64] = {0};
        snprintf(buf, 64, "%d", value);
        return buf;
    }

    string to_str( long value ) {
        char buf[64] = {0};
        snprintf(buf, 64, "%ld", value);
        return buf;
    }

    string to_str( long long value ) {
        char buf[64] = {0};
        snprintf(buf, 64, "%lld", value);
        return buf;
    }

    string to_str( unsigned value ) {
        char buf[64] = {0};
        snprintf(buf, 64, "%u", value);
        return buf;
    }

    string to_str( unsigned long value ) {
        char buf[64] = {0};
        snprintf(buf, 64, "%lu", value);
        return buf;
    }

    string to_str( unsigned long long value ) {
        char buf[64] = {0};
        snprintf(buf, 64, "%llu", value);
        return buf;
    }

    string to_str( float value ) {
        char buf[64] = {0};
        snprintf(buf, 64, "%f", value);
        return buf;
    }

    string to_str( double value ){
        char buf[64] = {0};
        snprintf(buf, 64, "%f", value);
        return buf;
    }

    string to_str( long double value ) {
        char buf[64] = {0};
        snprintf(buf, 64, "%Lf", value);
        return buf;
    }

    void str_split(const std::string & s, const std::string & delim, std::vector<std::string>& v) {

        if (s.empty() || delim.empty()) {
            return;
        }

        std::string::size_type i = 0;
        std::string::size_type pos = s.find(delim);
        if (pos == string::npos) {
            v.push_back(s);
        } else {
            while (pos != string::npos) {
                v.push_back(s.substr(i, pos-i));
                i = ++pos;
                pos = s.find(delim, pos);

                if (pos == string::npos) {
                    v.push_back(s.substr(i, s.length()));
                }
            }
        }
        return ;
    }

    string str_join(const vector<string> & vl, const string & connect_str) {
        string result;

        int size = vl.size();
        for (int i = 0; i < size; ++i) {
            if (i + 1 == size) {
                result += vl[i];
            } else {
                result += vl[i] + connect_str;
            }
        }
        return result;
    }

    string str_join_sides(const vector<string> & vl, const string &left_str,
            const string & right_str, const string & connect_str) {
        string result;

        int size = vl.size();
        for (int i = 0; i < size; ++i) {
            if (i + 1 != size) {
                result += left_str + vl[i] + right_str + connect_str;
            } else {
                result += left_str + vl[i] + right_str;
            }
        }
        return result;
    }

    void str_unique(vector<string> & vl) {
        sort(vl.begin(), vl.end());
        vl.erase(unique(vl.begin(), vl.end()), vl.end());
    }

    void str_toupper(string & str) {
        string::iterator it = str.begin();
        for (; it != str.end(); ++it) {
            *it = toupper(*it);
        }
    }

    void str_tolower(string & str) {
        string::iterator it = str.begin();
        for (; it != str.end(); ++it) {
            *it = tolower(*it);
        }
    }

    void str_trim(string & str) {
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

    string::size_type find_str_npos(const string & first,
            const string & second, unsigned int count) {

        string::size_type n_pos = 0, pos = string::npos;

        unsigned int index = 0, find_count = 0;
        for (unsigned int i = 0; i < count; ++i) {
            if ((pos = first.find(second, index)) == string::npos) {
                break;
            } else {
                find_count++;
                n_pos = pos;
                index += pos + second.size();
            }
        }
        return count == find_count ? n_pos : string::npos;
    }

}
