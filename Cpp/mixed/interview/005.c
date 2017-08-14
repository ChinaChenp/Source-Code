#include <stdio.h>

void get_sum_num(int *array, int size, int sum)
{
	int *begin = &array[0];
	int *end = &array[size-1];

	while(begin < end)
	{
		if(*begin + *end > sum)
		{
			end--;
		}
		else if(*begin + *end < sum)
		{
			begin++;
		}
		else
		{
			break;
		}
	}
	printf("[%d] = %d + %d\n", sum, *begin, *end);
}

int main()
{
	int array[]={1, 2, 3, 5, 8, 13};
	get_sum_num(array, 6, 5);	

	return 0;
}

