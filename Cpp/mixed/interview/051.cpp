#include <iostream>
#include <stdlib.h>
#include <queue>
#include <vector>
using namespace std;

/// 寻找最大的K个数
vector<int> topk(vector<int> &vec, int size)
{
	priority_queue<int, vector<int>, less<int> > pque;
	//priority_queue<int, vector<int>, greater<int> > pque; //最小
	for(vector<int>::const_iterator it = vec.begin();
			it != vec.end(); ++it)
	{
		if(pque.size() < size)
			pque.push(*it);
		else
		{
			if(pque.top() > *it)
			{
				pque.pop();
				pque.push(*it);
			}
		}
	}

	vector<int> re;
	while(!pque.empty())
	{
		re.push_back(pque.top());
		pque.pop();
	}
	return re;
}

int main (int argc, char *argv[])
{
	///init
	vector<int> test;
	srand(time(NULL));
	int size = atoi(argv[1]);
	for(int i=0; i<size; ++i)
	{
		int random = rand()%size;
		cout<<random<<" ";
		test.push_back(random);
	}
	cout<<endl;

	vector<int> re = topk(test, 5);
	///print
	cout << "The top K Values are:";
	for(vector<int>::iterator it = re.begin();
			it != re.end(); ++it)
	{
		cout << " " << *it;
	}
	cout << endl;

	return 0;
}
