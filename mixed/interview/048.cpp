#include <stdlib.h>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

///从@input_value 中提取@size个最小的数
std::priority_queue<int> min_value(const std::vector<int> & input_value, int minsize)
{
	std::priority_queue<int> Que;
	std::vector<int>::const_iterator it = input_value.begin();
	for( ; it != input_value.end(); ++it)
	{
		if(Que.size() < minsize)
			Que.push(*it);
		else
		{
			if(*it < Que.top())
			{
				Que.pop();
				Que.push(*it);
			}
		}
	}
	return Que;
}

int main(int argc, char * argv[])
{
	std::vector<int> test;
	int max = 100;

	srand(time(NULL));
	while(max--)
		test.push_back(::rand()%100 + 1);

	//call
	std::priority_queue<int> re = min_value(test, atoi(argv[1]));

	//print
	while(re.size() > 0)
	{
		cout<<re.top()<<" ";
		re.pop();
	}
	cout<<endl;
}
