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

int main()
{
    string val = "  jfdFFjjWOfjdkaBBjJk  ";
    strToUpper(val);
    cout << "-------" << val << "-------" << endl;
    strToLower(val);
    cout << "-------" << val << "-------" << endl;

    //trim
    strTrim(val);
    cout << "-------" << val << "-------" << endl;

    val = "  abdd";
    strTrim(val);
    cout << "-------" << val << "-------" << endl;

    val = "fdsjal  ";
    strTrim(val);
    cout << "-------" << val << "-------" << endl;

    val = "   ";
    strTrim(val);
    cout << "------#" << val << "#------" << endl;

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

    s = "11&22&33&44&55fjdalj&&&789";
    vector<string> ve;
    strSplit(s, "&", ve);
    print(ve);

    strUnique(strs);
    print(strs);

}
