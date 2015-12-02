#include <stdio.h>

int binary_search(int *array, int size, int key)
{
	int start = 0;
	int end = size;
	int mid = (start + end)/2;
	
	while(start < end)
	{
		mid = (start + end)/2;
		if(key > array[mid])
			start = ++mid;
		else if(key < array[mid])
			end = --mid;
		else
			return 1;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int m = atoi(argv[1]);
	int a[] = {1, 3, 6, 9, 12, 16, 18, 21, 32};
	printf("search %d---->%d\n", m, binary_search(a, 9, m));
	return 0;
}
