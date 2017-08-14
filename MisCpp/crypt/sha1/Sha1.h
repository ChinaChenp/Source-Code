//
// Author: Ping Chen
// Date: 2016.11.2
//

#ifndef SHA1_H_
#define SHA1_H_

#include <string>

namespace sha1 {

class CSha1 {
public:
    CSha1(const std::string & txt):m_txt(txt) {}
    ~CSha1(){}

    std::string result() {
        if (m_txt.empty()) {
            return "";
        }

        unsigned char hash[20] = {0};
        calc(m_txt.c_str(), m_txt.size(), hash);

        char hexstring[41] = {0};
        to_hex_str(hash, hexstring);

        return m_sha1.assign(hexstring);
    }

private:
    void to_hex_str(const unsigned char* hash, char* hexstring);
    void calc(const void* src, const int bytelength, unsigned char* hash);

    std::string m_sha1;
    std::string m_txt;
};

}
#endif // SHA1_H_
