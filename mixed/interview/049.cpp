#include <iostream>
#include <set>
#include <stdlib.h>
using namespace std;

///随机生成@num个整数且和为@sum
std::multiset<int> Random(int sum, int num)
{
	int diff = 0, last = 0;
	std::multiset<int> random, re;

	///随机划分num-1个点
	while(--num)
		random.insert(::rand() % (sum + 1));
	for(std::multiset<int>::iterator it = random.begin();
			it != random.end(); ++it)
	{
		diff = *it - last; ///按顺序计算每两个点之间差值 
		last = *it;
		re.insert(diff);
	}
	re.insert(sum - last);
	return re;
}

int main(int argc, char *argv[])
{
	srand(time(NULL));

	std::multiset<int> re = Random(atoi(argv[1]), atoi(argv[2]));
	
	//print
	std::multiset<int>::iterator it = re.begin();
	for(; it != re.end(); ++it)
		cout<<*it<<" ";
	cout<<endl;
}
