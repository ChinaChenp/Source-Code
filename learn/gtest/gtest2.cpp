#include <iostream>
#include </home/w/include/gtest/gtest.h>
using namespace std;
/*
 * Author: chenping <chenping@autohome.com.cn>
 *
 * File: gtest2.cpp
 * Create Date: 2015-01-19 14:53:58
 *
 */

///1.ASSERT_* 系列的断言,当检查点失败时,退出当前函数(注意:并非退出当前案例).
///2.EXPECT_* 系列的断言,当检查点失败时,继续往下执行.

/// (1)bool 检查
/// ASSERT_TRUE(condition);		EXPECT_TRUE(condition);		condition is true
/// ASSERT_FALSE(condition);	EXPECT_FALSE(condition);	condition is false

/// (2)数值类型检查
/// ASSERT_EQ(expected, actual);	EXPECT_EQ(expected, actual);	expected == actual
/// ASSERT_NE(val1, val2);			EXPECT_NE(val1, val2);			val1 != val2
/// ASSERT_LT(val1, val2);			EXPECT_LT(val1, val2);			val1 < val2
/// ASSERT_LE(val1, val2);			EXPECT_LE(val1, val2);			val1 <= val2
/// ASSERT_GT(val1, val2);			EXPECT_GT(val1, val2);			val1 > val2
/// ASSERT_GE(val1, val2);			EXPECT_GE(val1, val2);			val1 >= val2

/// (3)字符串检查
/// ASSERT_STREQ(expected_str, actual_str);		EXPECT_STREQ(expected_str, actual_str);		the two C strings have the same content
/// ASSERT_STRNE(str1, str2);					EXPECT_STRNE(str1, str2);					the two C strings have different content
/// ASSERT_STRCASEEQ(expected_str, actual_str);	EXPECT_STRCASEEQ(expected_str, actual_str);	the two C strings have the same content, ignoring case
/// ASSERT_STRCASENE(str1, str2);				EXPECT_STRCASENE(str1, str2);				the two C strings have different content, ignoring case

/// (1)测试断言
TEST(StringCmpTest, Demo)
{
	const char* pszCoderZh = "CoderZh";
	const wchar_t* wszCoderZh = L"CoderZh";
	std::string strCoderZh = "CoderZh";
	std::wstring wstrCoderZh = L"CoderZh";

	EXPECT_STREQ("CoderZh", pszCoderZh);
	EXPECT_STREQ(L"CoderZh", wszCoderZh);

	EXPECT_STRNE("CnBlogs", pszCoderZh);
	EXPECT_STRNE(L"CnBlogs", wszCoderZh);

	EXPECT_STRCASEEQ("coderzh", pszCoderZh);

	EXPECT_STREQ("CoderZh", strCoderZh.c_str());
	EXPECT_STREQ(L"CoderZh", wstrCoderZh.c_str());
}

/// (2)显示失败或成功
TEST(ExplicitTest, Demo)
{
	ADD_FAILURE() << "Sorry"; // None Fatal Asserton,继续往下执行.
	//FAIL();				  // Fatal Assertion,不往下执行该案例.
	SUCCEED();
}

/// (3)异常检查
int Foo(int a, int b)
{
	if (a == 0 || b == 0)
	{
		throw "don't do that";
	}
	int c = a % b;
	if (c == 0)
		return b;
	return Foo(b, c);
}

TEST(FooTest, HandleZeroInput)
{
	EXPECT_ANY_THROW(Foo(10, 0));
	EXPECT_THROW(Foo(0, 5), char*);
}


int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

