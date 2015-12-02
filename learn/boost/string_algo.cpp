#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/assign.hpp>
using namespace std;
/*
 * Author: chenping <chenping@autohome.com.cn>
 *
 * File: string_algo.cpp
 * Create Date: 2015-01-21 09:53:51
 *
 */

///
///  string操作
///  (1)i开头的函数表示忽略大小写
///  (2)带copy的表示有一次拷贝,以前的字符串不影响
///  (3)带if的表示满足条件的才执行
///

struct has_e
{
	bool operator()(const string &str)
	{return boost::contains(str, "e"); }
};

using namespace boost;
int main(int argc, char* argv[])
{
	//(判断前缀和后缀)starts_with,ends_with
	string str("name.txt");
	assert(boost::starts_with(str, "name") == true);
	assert(boost::ends_with(str, "txt") == true);

	//(替换)replace_first
	replace_first(str, "name", "readme");
	assert(str == "readme.txt");

	//(大小写转换)to_upper_copy
	assert(boost::to_upper_copy(str) == "README.TXT");
	assert(boost::to_lower_copy(str) == "readme.txt");
	boost::to_upper(str);
	assert(str == "README.TXT");
	boost::to_lower(str);
	assert(str == "readme.txt");

	//(删除第一次匹配的字符串)erase_first_copy
	string test("aaaa123df123f1234");
	assert(boost::erase_first_copy(test, "123") == "aaaadf123f1234");

	//(测试一个字符串是否包含另外一个)contains
	assert(boost::contains(test, "df"));
	
	//(检查一个字符串的所有元素是否满足指定判断式)all
	assert(boost::all(test.substr(0, 4), boost::is_lower()));

	//(修剪字符串两边)trim
	string test1("   hello world  ");
	boost::trim_left(test1);
	assert(test1 == "hello world  ");
	boost::trim_right(test1);
	assert(test1 == "hello world");

	//查找
	str = "Long long ago, there was a king.";
	boost::iterator_range<string::iterator> reg;
	reg = boost::find_first(str, "long"); // 查找第一次出现的位置
	if(reg.empty() && reg) //not null
		assert(string(reg.begin(), reg.end()) == "long");

	reg = boost::find_nth(str, "ng", 2); //查找第N次出现的位置
	assert(string(reg.begin(), reg.end()) == "ng");

	reg = boost::find_head(str, 4); //获取前4个字符
	assert(string(reg.begin(), reg.end()) == "Long");

	reg = boost::find_tail(str, 5); //获取前4个字符
	assert(string(reg.begin(), reg.end()) == "king.");

	//替换
	str = "Samus beat the monster.";
	assert(boost::replace_first_copy(str, "Samus", "samus") == "samus beat the monster.");
	boost::replace_last(str, "beat", "kill");
	assert(str == "Samus kill the monster.");

	//分割
	str = "Samus,Link.-+Zelda:::Mario-Luigi+zelda";
	std::deque<string> dq;
	boost::ifind_all(dq, str, "zelda"); //查找所有符合条件的字符串并插入到队列里面
	for(deque<string>::iterator it = dq.begin(); it != dq.end(); ++it)
		cout<<*it<<" ";
	cout<<endl;
	
	std::list<string> ll;
	boost::split(ll, str, boost::is_any_of(",.:-+"), boost::token_compress_on); //连续出现压缩成一个处理
	//boost::split(ll, str, boost::is_any_of(",.:-+"), boost::token_compress_on);
	for(std::list<string>::iterator it = ll.begin(); it != ll.end(); ++it)
		cout<<*it<<" ";
	cout<<endl;

	//合并
	std::vector<string> ve = boost::assign::list_of("hello")("I")("am")("chenping.");
	cout<<boost::join(ve, "+")<<endl;

	std::cout << boost::join_if(ve, "---", has_e()) << std::endl; 

	return 0;
}

