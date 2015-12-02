#include <stdio.h>

/// Follow up for ”Remove Duplicates”: What if duplicates are allowed at most twice?
/// For example, Given sorted array A = [1,1,1,2,2,3],
///	Your function should return length = 5, and A is now [1,1,2,2,3]

int array_unique2(int array[], int size, int times)
{
	int i = 1, time = 1;
	int index = 0;
	for(; i < size; ++i)
	{
		if(array[index] == array[i])
		{
			if(time < times)
			{
				array[++index] = array[i];
				time++;
			}
		}
		else
		{
			array[++index] = array[i];
			time = 1;
		}
	}
	return index + 1;
}

int main(int argc, char* argv[])
{
	int array[14] = {1, 1, 1, 2, 2, 4, 4, 4, 4, 9, 10, 10, 12, 13};
	int ret = array_unique2(array, 14, 2);

	//print
	int i = 0;
	for(; i < ret; ++i)
		printf("%d ", array[i]);
	printf("\n");
	return 0;
}

