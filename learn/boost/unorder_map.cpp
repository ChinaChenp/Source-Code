#include <iostream>
#include <boost/unordered_map.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/timer.hpp>

#include <map>
using namespace boost;
using namespace std;
/*
 * Author: chenping <chenping@autohome.com.cn>
 *
 * File: unorder_map.cpp
 * Create Date: 2015-02-01 11:18:16
 *
 */
//typedef map<int, string> Map;
typedef boost::unordered_map<int, string> Map;

int main(int argc, char* argv[])
{
	int total = atoi(argv[1]);
	
	boost::timer insert;
	Map mp;
	for(int i=0; i<total; ++i)
	{
		string s = lexical_cast<string>(i) + "chenp";
		mp.insert(make_pair<int, string>(i, s));
	}
	cout<<"insert total time = "<<insert.elapsed()<<endl;

	boost::timer find;
	for(int i=0; i<total; ++i)
	{
		mp.find(i);	
	}
	cout<<"find total time = "<<find.elapsed()<<endl;
	return 0;
}

