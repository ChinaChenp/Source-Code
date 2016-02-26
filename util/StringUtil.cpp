#include ""StringUtil.h""

namespace basetool {

    void strSplit(const string & str, const string & div_str, vector<std::string> value) {
        int size = str.size();
        std::string::size_type pos;
        for (int i = 0; i < size; ++i) {
            pos = str.find(div_str);
            if (pos != std::string::npos) {
                value.push_back(str.substr(i, pos-i));
                i = pos + div_str.size() + 1;
            }
        }
        return;
    }

    std::string strJoin(const std::vector<std::string> vl, const string & connect_str) {
        string result;

        int size = vl.size();
        for (int i=0; i< size; ++i) {
            if (i+1 != size) {
                result += vl[i] + connect_str;
            }
        }
        return result;
    }

    std::string strUnique(std::vector<std::string> & vl) {
         sort(vl.begin(), vl.end());
         vl.erase(unique(vl.begin(), vl.end()), vl.end());
    }

    void strToUpper(std::string & str) {
        std::string::iterator it = str.begin();
        for (; it != str.end(); ++it) {
            *it = topper(*it);
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

        string::iterator it  = str.begin();
    }
}
