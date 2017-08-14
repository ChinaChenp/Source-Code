#include <boost/algorithm/string.hpp>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void split(const std::string & s, const std::string & delim, std::vector<std::string>& v) {

    if (s.empty() || delim.empty()) {
        return;
    }

    std::string::size_type i = 0;
    std::string::size_type pos = s.find(delim);
    while (pos != string::npos) {
        v.push_back(s.substr(i, pos-i));
        i = ++pos;
        pos = s.find(delim, pos);

        if (pos == string::npos) {
            v.push_back(s.substr(i, s.length()));
        }
    }
}

int main () {
    vector<string> ve;
    string str = "&&&";
    split(str, "&", ve);
    cout << ve.size() << endl;
}
