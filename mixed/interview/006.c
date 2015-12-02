#include <stdio.h>

int return_sub_max(int *array, int size)
{
	int max_sum = array[0], temp = array[0];

	int i = 1;
	for( ; i<size; i++)
	{
		temp += array[i];
		if(temp > max_sum)
		{
			max_sum = temp;
		}	
		if(temp <= 0)
		{
			temp = 0;
		}
	}
	return max_sum;
}

int main()
{
	//int array[] = {-8, -2, -1, -3, -10, -4, -7, -2, -5};
	//int array[] = {1, 2, 3, -2, -3, 9};
	//int array[] = {1, -2, -3, 10, -4, 7, 2, -5};
	int array[] = {1, -9, 3, 10, 4, 7, 2, 5};

	int i = 0;
	int size = sizeof(array)/sizeof(int);
	for( ; i<size; ++i)
	printf("%d ", array[i]);
	printf("\nmax = %d\n", return_sub_max(&array[0], size));
	return 0;
}
