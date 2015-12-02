#include <iostream>
#include <boost/bind.hpp>
#include <boost/function.hpp>

using namespace std;
/*
 * Author: chenping <chenping@autohome.com.cn>
 *
 * File: bind2.cpp
 * Create Date: 2015-02-01 14:46:10
 *
 */

class demo_class
{
	typedef boost::function<void()> fun_t;
	fun_t fun_;
	int n_;
public:
	demo_class(int a):n_(a){}
	
	void accept(fun_t f)
	{fun_ = f;}
	
	void run()
	{fun_();}
};

class factory
{
public:
	void call_back1(int i)
	{
		cout<<"call back fun : "<<2*i<<endl;
	}
	void call_back2(int a, int b)
	{
		cout<<"call back fun2 : "<<(a+b)<<endl;
	}
};
void call_back1(int i)
{
	cout<<"call back fun : "<<2*i<<endl;
}
void call_back2(int a, int b)
{
	cout<<"call back fun2 : "<<(a+b)<<endl;
}
int main(int argc, char* argv[])
{
	demo_class de(100);
	de.accept(boost::bind(call_back1, 11));
	de.run();

	de.accept(boost::bind(call_back2, 11, 22));
	de.run();

	factory test;
	de.accept(boost::bind(&factory::call_back1, test, 11));
	de.run();
	
	de.accept(boost::bind(&factory::call_back2, test, 11, 22));
	de.run();

	typedef boost::function<void(int)> Fun;
	Fun f = call_back1;
	//Fun f = boost::bind(call_back1, _1);
	f(50);
	return 0;
}

