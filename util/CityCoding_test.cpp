#include <string>
#include <iostream>
#include <unistd.h>
#include "TestFramework.h"
#include "CityCoding.h"

using namespace std;

class CityCoding_test{};

TEST(CityCoding_test, province_test) {
    CCityCode data;
    int ret = data.load("./city_code.txt");
    ASSERT_EQ(0, ret);

    uint32 code = 110000;
    ret = data.isvalid_province(code);
    ASSERT_EQ(0, ret);

    code = 990000;
    ret = data.isvalid_province(code);
    ASSERT_EQ(1, ret);
}

TEST(CityCoding_test, coce_test) {
    CCityCode data;
    int ret = data.load("./city_code.txt");
    ASSERT_EQ(0, ret);

    string code = "110000", result;
    ret = data.isvalid(code, result);
    ASSERT_EQ(0, ret);
    ASSERT_EQ("北京市----", result);

    code = " 110000";
    ret = data.isvalid(code, result);
    ASSERT_EQ(0, ret);
    ASSERT_EQ("北京市----", result);

    code = "110000 ";
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

    code = "150403";
    ret = data.isvalid(code, result);
    ASSERT_EQ(0, ret);
    ASSERT_EQ("内蒙古自治区--赤峰市--元宝山区", result);

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

    code = "";
    ret = data.isvalid(code, result);
    ASSERT_EQ(-3, ret);

    code = "0";
    ret = data.isvalid(code, result);
    ASSERT_EQ(-3, ret);

    int codes = 110000;
    ret = data.isvalid(codes, result);
    ASSERT_EQ(0, ret);
    ASSERT_EQ("北京市----", result);

    codes = 120117;
    ret = data.isvalid(codes, result);
    ASSERT_EQ(0, ret);
    ASSERT_EQ("天津市--市辖区--宁河区", result);

    codes = 140321;
    ret = data.isvalid(codes, result);
    ASSERT_EQ(0, ret);
    ASSERT_EQ("山西省--阳泉市--平定县", result);

    codes = 441323;
    ret = data.isvalid(codes, result);
    ASSERT_EQ(0, ret);
    ASSERT_EQ("广东省--惠州市--惠东县", result);

    codes = 1100000;
    ret = data.isvalid(codes, result);
    ASSERT_EQ(-3, ret);
}

int main () {
    return leveldb::RunAllTests();
}

