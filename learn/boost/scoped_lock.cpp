#include <iostream>
//#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>

using namespace std;
/*
 * Author: chenping <chenping@autohome.com.cn>
 *
 * File: scoped_lock.cpp
 * Create Date: 2015-02-02 16:38:05
 *
 */

int main(int argc, char* argv[])
{
	//简单的加锁解锁
	boost::mutex mt;
	mt.lock();
	mt.unlock();

	//RAII mutex
	boost::mutex::scoped_lock lock(mt);
	return 0;
}

