#include <stdio.h>

void get_array_max_and_min(int *array, int array_size, int *max, int *min)
{
	if(array_size < 1)
		*max = *min = 0;
	else if(array_size == 1)
		*max = *min = array[0];

	if(array[0] > array[1])
		*max = array[0], *min = array[1];
	else
		*min = array[0], *max = array[1];

	int i=2;
	for(; i<array_size; ++i)
	{
		if(array[i] < *min)
			*min = array[i];
		else if(array[i] > *max)
			*max = array[i];
	}
}

int main()
{
	int array[] = {};
	//int array[] = {2, 5, 6, 9, 12, 38, 11, 9, 0, 7, 1, -2, 12};
	int max, min;
	get_array_max_and_min(array, sizeof(array)/sizeof(int), &max, &min);
	printf("max = %d, min = %d\n", max, min);
}
