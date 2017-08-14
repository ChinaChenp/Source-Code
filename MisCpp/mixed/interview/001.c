#include <stdio.h>

int find_repeat_num(int *array, int size)
{
	int i=0;
	int sum1 = 0, sum2 = 0;
	
	for(; i<size; ++i)
	{
		sum1 += i;
		sum2 += array[i];
	}
	return sum2 - sum1;
}

int main()
{
	int array[] = {1, 4, 3, 2, 5, 4};
	printf("---->%d\n", find_repeat_num(array, 6));
	return 0;
}
