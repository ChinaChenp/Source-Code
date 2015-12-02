#include <iostream>
#include <string.h>
#include <boost/smart_ptr.hpp>
using namespace std;

/*
* Author: chenping <chenping@autohome.com.cn>
*
* File: smart_ptr.cpp
* Create Date: 2015-01-21 13:11:45
*
*/

///
/// 智能指针的使用
///

struct posix_file
{
	posix_file(const char *file):file_(file)
	{cout<<"new file"<<file_<<endl;}
	~posix_file()
	{cout<<"delete file"<<file_<<endl;}
private:
	const char *file_;
};

class shared
{
	private:
		boost::shared_ptr<int> p_;
	public:
		shared(boost::shared_ptr<int> ptr):p_(ptr){}
		void print()
		{cout<<"class : value is = "<<*p_<<", use_count = "<<p_.use_count()<<endl;}
};
void print_fun(boost::shared_ptr<int> value)
{cout<<"fun : value is = "<<*value<<", use_count = "<<value.use_count()<<endl;}

int main(int argc, char* argv[])
{
	///
	/// scoped_ptr 独享的指针,所有权不能被转让
	/// (1) 不允许拷贝和赋值
	/// (2) 不需要delete
	/// (3) 不支持比较 ==, != 等
	/// (4) reset不应该被调用                                                                                                                                            
	/// (5) 不能放到容器中(不支持值拷贝)

	boost::scoped_ptr<int> pint(new int); //pint = new int //错误,没有赋值构造函数
	if(pint)
	{	*pint = 1000;
		cout<<"int is = "<<*pint<<endl;
	}
	pint.reset(); //pint is null
	assert(pint == NULL);
	boost::scoped_ptr<posix_file> pfile(new posix_file("./test.txt"));
	cout<<"de...."<<endl;

	/// shared_ptr
	/// (1)支持拷贝和赋值
	/// (2)支持任意的共享
	/// (3)可以放到容器中
	/// (4)reset()用于显示销毁对象,如果有多个对象只是当前指针停止对他引用
	/// 智能指针值递减
	boost::shared_ptr<string> pstr(new string);
	assert(pstr != NULL);
	*pstr = "init by pstr";
	cout<<"pstr = "<<*pstr<<endl;
	assert(pstr.unique() == 1); //唯一？
	boost::shared_ptr<string> pstr1 = pstr;
	assert(pstr == pstr1 && pstr1.use_count() == 2);
	*pstr1 = "change by pstr1";
	cout<<"pstr1 = "<<*pstr1<<endl;
	pstr1.reset();
	assert(pstr1 == NULL);
	assert(pstr.use_count() == 1);
	pstr.reset();  //马上析构

	//shared_ptr 复杂使用
	boost::shared_ptr<int> p(new int(10000));
	shared p1(p), p2(p);
	p1.print();
	p2.print();
	
	*p = 20000;
	print_fun(p);
	assert(p.use_count() == 3);
	p1.print();

	boost::shared_ptr<char> cp(new char[12]);
	strcpy(cp.get(), "chenp");
	cout<<cp<<endl;
	cout<<"----------------------------------------------"<<endl;
	return 0;
}
