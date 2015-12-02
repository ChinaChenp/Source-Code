#include <stdio.h>

/// Given a sorted array, remove the duplicates in place such that each element appear only
/// once and return the new length.
/// Do not allocate extra space for another array, you must do this in place with constant mem-
/// ory.
/// For example, Given input array A = [1,1,2],
///	Your function should return length = 2, and A is now [1,2].
/// 时间复杂度O(n), 空间复杂度O(1)

int array_unique(int array[], int size)
{
	int index = 0;
	for(int i = 1; i < size; ++i)
	{
		if(array[index] != array[i])
			array[++index] = array[i];
	}
	return index + 1;
}

int main(int argc, char* argv[])
{
	int array[12] = {1, 2, 2, 2, 3, 4, 6, 9, 10, 10, 12, 12};
	//int array[12] = {1, 1, 2, 2, 2, 3, 4, 6, 9, 10, 10, 12};
	int ret = array_unique(array, 12);

	//print result
	for(int i=0; i<ret; ++i)
		printf("%d ", array[i]);
	printf("\n");

	return 0;
}

