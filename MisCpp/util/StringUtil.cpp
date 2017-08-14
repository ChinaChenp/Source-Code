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
        if (vl.empty()) {
             return;
        }

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
        if (str.empty()) {
             return;
        }
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

    bool str_end_with(const string & str, const string & match) {
        return str.size() >= match.size() &&
            str.rfind(match) + match.size() == str.size();
    }

    bool str_start_with(const string & str, const string & match) {
        return str.size() >= match.size() &&
            str.substr(0, match.size()) == match;
    }

    string str_replace_all(const string & str, const string & old_str,
            const string & new_str) {
        if (old_str.empty()) {
            return str;
        }

        string re;
        string::size_type start_pos = 0;
        string::size_type pos;
        do {
            if ((pos = str.find(old_str, start_pos)) == string::npos) {
                break;
            }

            re.append(str.data() + start_pos, pos - start_pos);
            re.append(new_str.data(), new_str.size());
            start_pos = pos + old_str.size();
        }while(1);
        re.append(str.data() + start_pos, str.size() - start_pos);

        return re;
    }
}
