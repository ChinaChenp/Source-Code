#include <stdio.h>

void sort_array(int *array, int size)
{
	int *start = array;
	int *end = &array[size-1];
	int temp = 0;

	while(start < end)
	{
		if(*start%2 != 0)
		{
			start++;
			continue;
		}
		
		if(*end%2 == 0)
		{
			end--;
			continue;
		}

		temp = *start;
		*start = *end;
		*end = temp;
	}
}

void print(int *array, int size)
{
	int i=0;
	for(;i <size; i++)
		printf(" %d", array[i]);
	printf("\n");
}

int main()
{
	int array[] = {38, 1,2,4,6,7, 9,11, 12,38};
    //int in[]={9, 4, 3, 2,100, 99, 88, 77, 66, 6, 5, 4, 8, 3, 2};
	int size = sizeof(array)/sizeof(int);
	sort_array(array, size);
	print(array, size);
	
	return 0;
}
