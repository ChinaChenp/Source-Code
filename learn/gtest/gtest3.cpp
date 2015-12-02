#include <iostream>
#include </home/w/include/gtest/gtest.h>
using namespace std;
/*
 * Author: chenping <chenping@autohome.com.cn>
 *
 * File: gtest3.cpp
 * Create Date: 2015-01-19 15:30:38
 *
 */

/// 事件通知

/// 1.全局的,所有案例执行前后.
/// 2.TestSuite级别的,在某一批案例中第一个案例前,最后一个案例执行后.
/// 3.TestCase级别的,每个TestCase前后.

/// (1) 全局
class FooEnvironment : public testing::Environment
{
	public:
		virtual void SetUp()
		{
			std::cout << "-----------Foo FooEnvironment SetUP-----------" << std::endl;
		}
		virtual void TearDown()
		{
			std::cout << "------------Foo FooEnvironment TearDown-----------" << std::endl;
		}
};

TEST(FooTest, case0)
{
	EXPECT_EQ(2, 2);
}

TEST(FooTest, case1)
{
	EXPECT_EQ(6, 6);
}

TEST(FooTest1, case0)
{
	EXPECT_EQ(6, 6);
}

TEST(FooTest1, case1)
{
	EXPECT_EQ(6, 6);
}

/// ()
class FooTest : public testing::Test 
{
protected:
	static void SetUpTestCase() 
	{
		//shared_resource_ = new;
		std::cout << "--------------SetUpTestCase--------------" << std::endl;
	}
	static void TearDownTestCase() 
	{
		std::cout << "--------------TearDownTestCase-------------------" << std::endl;
		//delete shared_resource_;
	}
	static FooTest * shared_resource_;
};

/// (3) TestCase 每个案列执行前后
class FooCalcTest:public testing::Test
{
	protected:
		virtual void SetUp()
		{
			std::cout << "-----------Footest1 case begin-----------" << std::endl;
		}
		virtual void TearDown()
		{
			std::cout << "-----------Footest1 case end-----------" << std::endl;
		}
};

TEST_F(FooCalcTest, HandleNoneZeroInput)
{
	EXPECT_EQ(4, 4);
}

TEST_F(FooCalcTest, HandleNoneZeroInput_Error)
{
	EXPECT_EQ(5, 4);
}

int main(int argc, char *argv[])
{
	testing::AddGlobalTestEnvironment(new FooEnvironment);
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

