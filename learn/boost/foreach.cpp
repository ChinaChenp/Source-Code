#include <iostream>
#include <boost/foreach.hpp>
#include <boost/assign.hpp>
#include <vector>
#include <map>

using namespace boost::assign;
using namespace std;
/*
 * Author: chenping <chenping@autohome.com.cn>
 *
 * File: foreach.cpp
 * Create Date: 2015-02-01 10:29:56
 *
 */

int main(int argc, char* argv[])
{
	//vector
	vector<int> vc= list_of(1)(2)(3)(4);
	BOOST_FOREACH(int x, vc)
	{
		cout<<x<<" ";
	}
	cout<<endl;

	BOOST_REVERSE_FOREACH(int x, vc)
	{
		cout<<x<<" ";
	}
	cout<<endl;

	//map
	map<int, string>mp = map_list_of(1, "chenp")(2, "xunbo")(3, "unknow");
	typedef map<int, string>::value_type Pair;
	BOOST_FOREACH(Pair & re, mp)
	{
		cout<<re.first<<"--->"<<re.second<<endl;
	}
	
	//double vector
	vector<vector<int> > dve;
	dve.push_back(list_of(1)(2)(3));
	dve.push_back(list_of(5)(6)(7));
#if 1
	BOOST_FOREACH(vector<int> &tmp, dve)
	{
		BOOST_REVERSE_FOREACH(int & re, tmp)
		{
			cout<<re<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
#else
	for(int i=0; i<dve.size(); ++i)
	{
		vector<int> &re = dve[i];
		for(int j=0; j<re.size(); ++j)
			cout<<re[j]<<" ";
		cout<<endl;
	}
#endif
	return 0;
}

