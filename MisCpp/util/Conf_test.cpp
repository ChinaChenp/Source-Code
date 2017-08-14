#include <string>
#include <iostream>
#include <unistd.h>
#include "TestFramework.h"
#include "Conf.h"

using namespace std;
using namespace basetool;

class Conf_test{};

TEST(Conf_test, kv_test) {
    Conf::initConf("./conf.cf");

    ASSERT_EQ(Conf::getString("teststring"), "chenping");
    ASSERT_EQ(Conf::getString("teststring1"), "chenping");
    ASSERT_EQ(Conf::getString("teststring2"), "chenping");
    ASSERT_EQ(Conf::getString("teststring3"), "chenping");
    ASSERT_EQ(Conf::getString("teststring4"), "");
    ASSERT_EQ(Conf::getString("teststring5"), "");

    ASSERT_EQ(Conf::getInt("testint"), 123);
    ASSERT_EQ(Conf::getInt64("testint64"), 1234567890123456);

    float diff = Conf::getFloat("testfloat") - 12.3456;
    ASSERT_LE(diff, 0.000001);
}

TEST(Conf_test, other_process) {
    string teststring = Conf::getString("teststring");
    cout << "teststring = " << teststring << endl;
    ASSERT_EQ(teststring, "chenping");

    int testint = Conf::getInt("testint");
    cout << "testint = " << testint << endl;
    ASSERT_EQ(testint, 123);

    long long testint64 = Conf::getInt64("testint64");
    cout << "testint64 = " << testint64 << endl;
    ASSERT_EQ(testint64, 1234567890123456);

    float testfloat = Conf::getFloat("testfloat");
    cout << "testfloat = " << testfloat << endl;
    //ASSERT_EQ(testfloat, 12.3456);
}

TEST(Conf_test, defualt) {
    ASSERT_EQ(Conf::getString("stringdefault", "stringdefault"), "stringdefault");
    ASSERT_EQ(Conf::getInt("testintdefault", 1234), 1234);
    ASSERT_EQ(Conf::getInt64("testint64default", 1234567890), 1234567890);
    float diff = Conf::getFloat("testfloatdefault", 12.3456) - 12.3456;
    ASSERT_LE(diff, 0.000001);
}


int main () {
    return leveldb::RunAllTests();
}

