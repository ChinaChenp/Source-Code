#include <string>
#include <iostream>
#include "StringUtil.h"

using namespace std;
using namespace basetool;

void print(vector<string> & ve){
    for (int i = 0; i<ve.size(); ++i) {
         cout<< ve[i] << "-";
    }
    cout<<endl;
}

void debug(const string & oldstr, const string & newstr, const string & name) {
    cout << "---" << oldstr << "--- " << name << " ---" << newstr << "---" << endl;
}

int main()
{
    string val = "  jfdFFjjWOfjdkaBBjJk  ";
    string temp = val;
    strToUpper(val);
    debug(temp, val, "upper");

    strToLower(val);
    debug(temp, val, "lower");

    //trim
    strTrim(val);
    debug(temp, val, "trim");

    val = "  abdd";
    strTrim(val);
    debug(temp, val, "trim");

    val = "fdsjal  ";
    strTrim(val);
    debug(temp, val, "trim");

    val = "   ";
    strTrim(val);
    debug(temp, val, "trim");

    //join
    vector<string> strs;
    strs.push_back("12345");
    strs.push_back("12345");
    strs.push_back("12346");
    strs.push_back("12347");
    strs.push_back("12345");
    strs.push_back("12348");
    strs.push_back("12349");

    string s = strJoin(strs, " or ");
    cout << "------#" << s << "#------" << endl;

    s = "11 &22&33&44&55fjdalj&&&789 ";
    vector<string> ve;
    strSplit(s, "&", ve);
    print(ve);

    strUnique(strs);
    print(strs);

}
