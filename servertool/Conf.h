#ifndef BASE_TOOL_CONF_H_
#define BASE_TOOL_CONF_H_

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/unordered_map.hpp>
#include <boost/lexical_cast.hpp>
#include <string>
#include <vector>

///
/// ini conf
///

namespace basetool
{

using namespace std;
using namespace boost;

class Conf
{
public:
	explicit Conf(const string &pathfile);
	
	void put(const string &node);

	template<typename T>
	static const T get(const string &node)
	{ 
		string re(" ");
		boost::unordered_map<string, string>::iterator it;
		if((it = cache_.find(node)) != cache_.end())
			re = it->second;
		else
			fprintf(stderr,"config note %s not find.", node.c_str());
		return boost::lexical_cast<T>(re);
	}

	string pathName()
	{ return pathfile_; }

private:

	string pathfile_;
	boost::property_tree::ptree tree_;
	static boost::unordered_map<string, string> cache_;
};

}
#endif //BASE_TOOL_CONF_H_
