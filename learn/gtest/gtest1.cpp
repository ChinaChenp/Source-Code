#include <iostream>
#include </home/w/include/gtest/gtest.h>

using namespace std;
/*
 * Author: chenping <chenping@autohome.com.cn>
 *
 * File: gtest1.cpp
 * Create Date: 2015-01-18 16:29:02
 *
 */

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


TEST(FooTest, HandleNoneZeroInput)
{
	EXPECT_EQ(2, Foo(4, 10));
	EXPECT_EQ(6, Foo(30, 18));
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

