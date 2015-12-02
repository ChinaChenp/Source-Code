#include <iostream>
#include <boost/lexical_cast.hpp>
using namespace std;
/*
 * Author: chenping <chenping@autohome.com.cn>
 *
 * File: lexical_cast.cpp
 * Create Date: 2015-01-21 09:43:01
 *
 */

///
/// 数值和字符串转换
///

int main(int argc, char* argv[])
{
	using namespace boost;
	//int,long,float,double
	int x = lexical_cast<int>("1000");
	long y = lexical_cast<long>("1001");

	string a = lexical_cast<string>("1111111");
	string b = lexical_cast<string>(123.22222);
	cout<<x<<", "<<y<<", "<<a<<", "<<b<<endl;
	return 0;
}

