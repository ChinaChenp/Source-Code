#include <string>
#include <iostream>
#include <unistd.h>
#include "TestFramework.h"
#include "CityCoding.h"

using namespace std;

class CityCoding_test{};

TEST(CityCoding_test, find) {
    CCityCode data;
    int ret = data.load("./city_code.txt");
    ASSERT_EQ(0, ret);

    string code = "110000", result;
    ret = data.isvalid(code, result);
    ASSERT_EQ(0, ret);
    ASSERT_EQ("北京市----", result);

    code = "810000";
    ret = data.isvalid(code, result);
    ASSERT_EQ(0, ret);
    ASSERT_EQ("香港特别行政区----", result);

    code = "820000";
    ret = data.isvalid(code, result);
    ASSERT_EQ(0, ret);
    ASSERT_EQ("澳门特别行政区----", result);

    code = "820000";
    ret = data.isvalid(code, result);
    ASSERT_EQ(0, ret);
    ASSERT_EQ("澳门特别行政区----", result);

    code = "130202";
    ret = data.isvalid(code, result);
    ASSERT_EQ(0, ret);
    ASSERT_EQ("河北省--唐山市--路南区", result);

    code = "450107";
    ret = data.isvalid(code, result);
    ASSERT_EQ(0, ret);
    ASSERT_EQ("广西壮族自治区--南宁市--西乡塘区", result);

    code = "a123454";
    ret = data.isvalid(code, result);
    ASSERT_EQ(-3, ret);

    code = "100000";
    ret = data.isvalid(code, result);
    ASSERT_EQ(-3, ret);

    code = "1000000";
    ret = data.isvalid(code, result);
    ASSERT_EQ(-3, ret);

    code = "110010";
    ret = data.isvalid(code, result);
    ASSERT_EQ(-5, ret);
}

int main () {
    return leveldb::RunAllTests();
}

