#include <string>
#include <iostream>
#include <unistd.h>
#include "TestFramework.h"
#include "UrlCodec.h"

using namespace std;
using namespace basetool;

class UrlCodec_test {};

TEST(UrlCodec_test, decode) {
    string result;
    char * url = "https://www.google.ca/?gws_rd=ssl#q=url+decoding";
    result = UrlEncode(url);
    ASSERT_EQ(result, "https%3A%2F%2Fwww.google.ca%2F%3Fgws_rd%3Dssl%23q%3Durl%2Bdecoding");


    //space
    result = UrlDecode("%20");
    ASSERT_EQ(result, " ");

    // string with space
    result = UrlDecode("ASDF%20ASDF");
    ASSERT_EQ(result, "ASDF ASDF");

    // only %%
    result = UrlDecode("%%");
    ASSERT_EQ(result, "%%");

    result = UrlDecode("%%%%");
    ASSERT_EQ(result, "%%%%");

    result = UrlDecode("%%%%29");
    ASSERT_EQ(result, "%%%)");

    // !"#$&'()'"
    result = UrlDecode("%20%21%22%23%24%26%27%28%29");
    cout << result << endl;
    ASSERT_EQ(result, " !\"#$&'()");

    result = UrlDecode("a +c+d");
    ASSERT_EQ(result, "a  c d");
}

int main () {
    return leveldb::RunAllTests();
}

