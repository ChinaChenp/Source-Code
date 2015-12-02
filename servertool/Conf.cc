#include "Conf.h"

namespace basetool
{
	boost::unordered_map<string, string> Conf::cache_;

	Conf::Conf(const string &pathfile)
		:pathfile_(pathfile)
	{ 
		boost::property_tree::ini_parser::read_ini(pathfile, tree_); 
	}

	void Conf::put(const string &node)
	{
		cache_[node] = tree_.get<string>(node);
	}
}

