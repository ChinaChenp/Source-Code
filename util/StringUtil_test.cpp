#include <string>
#include <iostream>
#include <unistd.h>
#include "TestFramework.h"
#include "StringUtil.h"

using namespace std;
using namespace basetool;

//void print(vector<string> & ve){
//    for (int i = 0; i<ve.size(); ++i) {
//         cout<< ve[i] << "-";
//    }
//    cout<<endl;
//}
//
//void debug(const string & oldstr, const string & newstr, const string & name) {
//    cout << "---" << oldstr << "--- " << name << " ---" << newstr << "---" << endl;
//}

class StringUtilTest {};

TEST(StringUtilTest, upper_domn) {
    string val = "  jfdFFjjWOfjdkaBBjJk  ";
    string temp = val;
    str_toupper(val);
    ASSERT_EQ(val, "  JFDFFJJWOFJDKABBJJK  ");

    str_tolower(val);
    ASSERT_EQ(val, "  jfdffjjwofjdkabbjjk  ");
}

TEST(StringUtilTest, trim) {
    string val = "  jfdFFjjWOfjdkaBBjJk  ";
    str_trim(val);
    ASSERT_EQ(val, "jfdFFjjWOfjdkaBBjJk");

    val = "  abdd";
    str_trim(val);
    ASSERT_EQ(val, "abdd");

    val = "fdsjal  ";
    str_trim(val);
    ASSERT_EQ(val, "fdsjal");

    val = "   ";
    str_trim(val);
    ASSERT_EQ(val, "");
}

TEST(StringUtilTest, join_split) {
    //join
    vector<string> strs;
    strs.push_back("12345");
    strs.push_back("12345");
    strs.push_back("12346");
    strs.push_back("12347");

    string s = str_join(strs, " or ");
    ASSERT_EQ(s, "12345 or 12345 or 12346 or 12347");

    s = "11 &22&33&44&55fjdalj&&&789 ";
    vector<string> vec;
    str_split(s, "&", vec);
    ASSERT_EQ(vec[0], "11 ");
    ASSERT_EQ(vec[1], "22");
    ASSERT_EQ(vec[6], "");
    ASSERT_EQ(vec[7], "789 ");

    s = "&&22&";
    vector<string> vec1;
    str_split(s, "&", vec1);
    ASSERT_EQ(vec1.size(), 4);
    ASSERT_EQ(vec1[0], "");
    ASSERT_EQ(vec1[1], "");
    ASSERT_EQ(vec1[2], "22");
    ASSERT_EQ(vec1[3], "");

    s = "";
    vector<string> vec2;
    str_split(s, "&", vec2);
    ASSERT_EQ(vec2.size(), 0);
}

TEST(StringUtilTest, uniq) {
    vector<string> ve;
    ve.push_back("11");
    ve.push_back("22");
    ve.push_back("11");
    ve.push_back("33");
    ve.push_back("22");
    usleep(500);

    str_unique(ve);
    ASSERT_EQ("11", ve[0]);
    ASSERT_EQ("22", ve[1]);
    ASSERT_EQ("33", ve[2]);
}

TEST(StringUtilTest, find_str_npos) {
    string src = "http://http://";
    string::size_type n = find_str_npos(src, "http://", 1);
    ASSERT_EQ(n, 0);

    n = find_str_npos(src, "http://", 2);
    ASSERT_EQ(n, 7);
    ASSERT_EQ("http://", src.substr(0, n));

    n = find_str_npos(src, "http://", 3);
    ASSERT_EQ(n, string::npos);
}

int main () {
    return leveldb::RunAllTests();
}

