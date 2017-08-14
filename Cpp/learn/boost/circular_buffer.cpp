#include <iostream>
#include <boost/circular_buffer.hpp>
#include <boost/foreach.hpp>
#include <boost/assign.hpp>
using namespace boost::assign;
using namespace std;
/*
 * Author: chenping <chenping@autohome.com.cn>
 *
 * File: circular_buffer.cpp
 * Create Date: 2015-02-01 12:17:33
 *
 */

void print(boost::circular_buffer<int> & cr)
{
	BOOST_FOREACH(int re, cr)
	{
		cout<<re<<" ";
	}
	cout<<endl;
}

int main(int argc, char* argv[])
{
	boost::circular_buffer<int> cr = list_of(1)(2)(3)(4)(5)(6);
	print(cr);

	assert(!cr.empty());
	assert(cr.full());
	cr.push_back(7);
	print(cr);
	cr.push_front(0);
	print(cr);
	assert(cr.front() == 0);
	assert(cr.size() == 6);
	assert(cr[1] == 2);
	return 0;
}

