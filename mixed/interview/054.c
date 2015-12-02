#include <stdio.h>
#include <stdlib.h>

/// Suppose a sorted array is rotated at some pivot unknown to you beforehand.
/// (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
/// You are given a target value to search. If found in the array return its index, otherwise return -1.
/// You may assume no duplicate exists in the array.

// 二分查找边界判断
// 时间复杂度 O(log n)，空间复杂度 O(1)
int search(int array[], int size, int obj)
{
	int mid = 0;
	int first = 0, last = size;

	while(first != last)
	{
		mid = (first + last)/2;
		if(obj == array[mid])
			return mid;
		if(obj <= array[mid])
		{
			if(array[first] <= obj && array[mid] > obj)
				last = mid;
			else
				first = mid + 1;
		}
		else
		{
			if(array[last] >= obj && array[mid] < obj)
				first = mid + 1;
			else
				last = mid;
		}
	}
	return -1;
}

int main(int argc, char* argv[])
{
	int array[] = {4, 5, 7, 9, 10, 14, 0, 1, 2, 3};
	int index = search(array, 10, atoi(argv[1]));
	printf("index of array is %d\n", index);
	return 0;
}

