#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

int get_last_digit_from_ring(int ring_size, int del_number)
{
	int i;
	vector<int> circle;
	for(i=0; i<ring_size; ++i)
	{
		circle.push_back(i+1);
	}

	vector<int>::iterator it = circle.begin();
	while(circle.size() > 1)
	{
		for(i=1; i<del_number; ++i)
		{
			++it;
			if(it == circle.end())
				it = circle.begin();
		}
		
		it = circle.erase(it);
		if(it == circle.end())
			it = circle.begin();
	}
	return *it;
}

int main()
{
	int ret = get_last_digit_from_ring(5, 3);
	cout<<"last digit--->"<<ret<<endl;
	return 0;
}
