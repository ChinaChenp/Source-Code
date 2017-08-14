#include <iostream>
#include <cstdlib>

using namespace std;

const int SHUFFLE_TIMES = 1024;

void Show(int *array, int size)
{
	int i=0;
	for(i=0; i<size; ++i)
		cout<<" "<<array[i];
	cout<<endl;
}

void Swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
** 方法一、随机交换两个数组值,当交换次数越多越随机
*/
void shuffle_1(int *array, int size)
{
	int r1, r2;
	int count = rand()%SHUFFLE_TIMES;
	while(count--)
	{
		r1 = rand()%size;
		r2 = rand()%size;
		Swap(&array[r1], &array[r2]);
	}
}

/*
** 方法二、顺序遍历一次数组,然后从剩下的数组中取出一个与其交换
** 时间复杂度O(n),空间复杂度O(0)
*/
void shuffle(int *array, int size)
{
	int i = 0;
	for(i=size-1; i>0; --i)
	{
		Swap(&array[i], &array[rand()%i]);
	}
}


int main()
{
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
	int size = sizeof(a)/sizeof(int);
	shuffle(a, size);
	Show(a, size);
	shuffle_1(a, size);
	Show(a, size);
	return 0;
}
