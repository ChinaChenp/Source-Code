#include <iostream>
#include <boost/noncopyable.hpp>
using namespace std;
/*
 * Author: chenping <chenping@autohome.com.cn>
 *
 * File: noncopyable.cpp
 * Create Date: 2015-01-26 16:23:58
 *
 */


class no_copy: boost::noncopyable
{

};

int main(int argc, char* argv[])
{
	no_copy a;
	//no_copy b(a); //error
	no_copy c;
	//c = a;   //error
	return 0;
}

