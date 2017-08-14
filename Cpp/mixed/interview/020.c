#include <stdio.h>
/*
** method one
*/
int find_int_more_than_half(int *array, int size)
{
	int i = 1;
	int count = 1;
	int temp = array[0];
	for(; i<size; ++i)
	{
		if(count == 0)
		{
			temp = array[i];
			count++;
			continue;
		}
		if(temp == array[i])
			count++;
		else
			count--;
	}
	return temp;
}


/*
** hash
*/
int find_int_more_than_half_1(int *array, int size)
{
	int i=0; 
	int	hash[65536] = {0};
	for(; i<size; ++i)
	{
		hash[array[i]]++;
	}
	for(i=0; i<65536; ++i)
	{
		if(hash[i] > size/2)
			return i;
	}
	return 0;
}

/*
** sort
*/
int find_int_more_than_half_2(int *array, int size)
{
	/*sort*/
	int i = 0, j = 0;
	int temp;
	for(i=0; i<size-1; i++)
	{
		for(j=i+1; j<size; j++)
		{
			if(array[i] > array[j])
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
	return array[size/2];
}

int main()
{
	//int a[] = {1,2,1};
	//int a[] = {1,1,1,2,4};
	//int a[] = {1,2,2,4, 2,6,2};
	int a[] = {1,3,3,3,2,2,2,1,1,2,1,1,4,1,1,4,1,1,1};
	//int a[] = {1,3,2,1,1,2,4,1,1};

	printf("--->%d\n", find_int_more_than_half(a, sizeof(a)/sizeof(int)));
	printf("--->%d\n", find_int_more_than_half_1(a, sizeof(a)/sizeof(int)));
	printf("--->%d\n", find_int_more_than_half_2(a, sizeof(a)/sizeof(int)));
	return 0;
}
