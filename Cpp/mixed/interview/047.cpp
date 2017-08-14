#include <iostream>
using namespace std;

void show(int *array, int size)
{
	int i = 0; 
	for(; i<size; ++i)
		cout<<" "<<array[i];
	cout<<endl;
}

void get_long_pos(int *array, int size)
{
	int *fast = array, *slow = array; 
	int *pos;

	int tmp = 0, len = 0;
	while(fast != &array[size])
	{
		while(*fast != 1)
		{
			fast++;
			continue;
		}
		slow = fast;
		while(*fast != 0 && fast != &array[size])
			fast++;
		tmp = fast - slow;
		if(tmp > len)
		{
			pos = slow;
			len = tmp;
		}
		slow = fast;
	}
	cout<<"["<<pos-array<<","<<pos-array+len-1<<"]"<<endl;
}

int main()
{
	int a[] = {0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1};
	int size = sizeof(a)/sizeof(int);
	show(a, size);
	get_long_pos(a, size);
}

