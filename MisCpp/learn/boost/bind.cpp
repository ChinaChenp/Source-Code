#include <iostream>
#include <boost/bind.hpp>
using namespace std;
/*
 * Author: chenping <chenping@autohome.com.cn>
 *
 * File: bind.cpp
 * Create Date: 2015-02-01 14:03:45
 *
 */
int ok()
{return 0;}

int f(int a, int b)
{return a+b;}

int g(int a, int b, int c)
{return a+b+c;}

typedef int (*f_tpye)(int a, int b);
typedef int (*g_type)(int a, int b, int c);

class demo
{
public:
	int ok()
	{return 1;}
	int fun(int a, int b)
	{return a+b;}
};

int main(int argc, char* argv[])
{
	//普通函数
	cout<<boost::bind(ok)()<<endl;
	cout<<boost::bind(f, 1, 2)()<<endl;
	cout<<boost::bind(g, 1, 2, 3)()<<endl;

	int x=11, y=22;
	cout<<boost::bind(f, _1, 2)(x)<<endl; //f(11, 2)
	cout<<boost::bind(f, _1, _2)(x, y)<<endl; //f(x, y)
	cout<<boost::bind(g, _1, 2, _2)(x, y)<<endl; //g(11, 2, 22)

	//函数指针
	f_tpye f_fun = f;
	g_type g_fun = g;

	cout<<boost::bind(f_fun, 1, 2)()<<endl;
	cout<<boost::bind(g_fun, 1, 2, 3)()<<endl;

	//成员函数
	demo d1, &d2=d1;
	demo *d3 = &d1;
	cout<<boost::bind(&demo::ok, d1)()<<endl;
	cout<<boost::bind(&demo::fun, d1, 11, 22)()<<endl;
	cout<<boost::bind(&demo::fun, d2, _1, 22)(10)<<endl;
	cout<<boost::bind(&demo::fun, d3, 11, _1)(11)<<endl;
	return 0;
}

