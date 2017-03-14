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

    s = "aaaaa";
    vector<string> vec3;
    str_split(s, "&", vec3);
    ASSERT_EQ(vec3.size(), 1);
    ASSERT_EQ(vec3[0], "aaaaa");
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

TEST(StringUtilTest, end_with) {
    string str = "chenp";
    string match = "ch";
    ASSERT_EQ(str_end_with(str, match), false);

    match = "np";
    ASSERT_EQ(str_end_with(str, match), true);

    str = " ";
    match = "";
    ASSERT_EQ(str_end_with(str, match), true);

    str = " ";
    match = " ";
    ASSERT_EQ(str_end_with(str, match), true);

    str = "";
    match = "";
    ASSERT_EQ(str_end_with(str, match), true);

    str = "short_str";
    match = "short str long";
    ASSERT_EQ(str_end_with(str, match), false);
}

TEST(StringUtilTest, start_with) {
    string str = "chenp";
    string match = "ch";
    ASSERT_EQ(str_start_with(str, match), true);

    match = "np";
    ASSERT_EQ(str_start_with(str, match), false);

    str = " ";
    match = "";
    ASSERT_EQ(str_start_with(str, match), true);

    str = " ";
    match = " ";
    ASSERT_EQ(str_start_with(str, match), true);

    str = "";
    match = "";
    ASSERT_EQ(str_start_with(str, match), true);

    str = "short_str";
    match = "short str long";
    ASSERT_EQ(str_start_with(str, match), false);
}

TEST(StringUtilTest, replace_all) {
    string str= "1 2 3 1";
    string re = str_replace_all(str, " ", "bb");
    ASSERT_EQ(re, "1bb2bb3bb1");

    re = str_replace_all(str, " 2", "A");
    ASSERT_EQ(re, "1A 3 1");

    re = str_replace_all(str, "1", "");
    ASSERT_EQ(re, " 2 3 ");
}

int main () {
    return leveldb::RunAllTests();
}

