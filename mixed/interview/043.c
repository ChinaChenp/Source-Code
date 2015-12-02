#include <stdio.h>

static void swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void display(int *array, int size)
{
	int i=0; 
	for(; i<size; ++i)
		printf(" %02d", array[i]);
	printf("\n");
}

void bubble_sort(int *array, int size)
{
	int i,j;
	for(i=0; i<size-1; ++i)
	{
		for(j=i+1; j<size; ++j)
		{
			if(array[i] > array[j])
				swap(&array[i], &array[j]);
		}
	}
}

void select_sort(int *array, int size)
{
	int i, j, min;
	for(i=0; i<size-1; ++i)
	{
		min = i;
		for(j=i+1; j<size; ++j)
		{
			if(array[i] > array[j])
			{
				min = j;
				break;
			}
		}
		if(min != i)
			swap(&array[i], &array[j]);
	}
}

void quick_sort(int *array, int begin, int end)
{
	int left = begin;
	int right = end;
	
	int split = array[begin];
	while(left <= right)
	{
		while(array[left] < split && left < end)
			left++;
		while(array[right] > split && right > begin)
			right--;
		if(left <= right)
			swap(&array[left++], &array[right--]);
	}
	if(left < end)
		quick_sort(array, left, end);
	if(right > begin)
		quick_sort(array, begin, right);
}

void insert_sort(int *array, int size)
{
	int i, j, tmp;
	const int width = 1;
	for(i=width; i<size; ++i)
	{
		tmp = array[i];
		
		j = i-width;
		while(j >= 0 && tmp < array[j])
		{
			array[j+width] = array[j];
			j -= width;
		}
		array[j+width] = tmp;
	}
}

void shell_sort(int *array, int size)
{
	int i, j, tmp;

	int width = size/2;
	while(width >= 1)
	{
		for(i=width; i<size; ++i)
		{
			tmp = array[i];
			
			j = i - width;
			while(j>=0 && tmp < array[j])
			{
				array[j+width] = array[j];
				j -= width;
			}
			array[j+width] = tmp;
		}
		width /= 2;
	}
}

void heap_update(int *array, int current, int top)
{
	int i = current;
	int j = 2*i;
	int tmp = array[current];
	
	while(j <= top)
	{
		if(j < top && array[j] < array[j+1])
			j++;
	
		if(array[j] <= tmp)
			break;
		
		{
			array[i] = array[j];
			i = j;
			j = 2*i;
		}
	}
	array[i] = tmp;
}

void heap_sort(int *array, int size)
{
	int i;
	for(i=size/2; i>0;--i)
		heap_update(array, i, size);
	
	for(i=size; i>=2; i--)
	{
		swap(&array[1], &array[i]);
		heap_update(array, 1, i-1);
	}
}


int main(int argc, char *argv[])
{
	int a[] = {5, 12, 67, 9, 20, 13, 16, 21, 90, 54, 32, 61, 90, 101, 3, 2, 7, 8};
	int size = sizeof(a)/sizeof(int);

	printf("%-8s", "before: ");
	display(a, size);

	switch(atoi(argv[1]))
	{
	case 1:
		printf("bubble_sort: ");
		bubble_sort(a, size);
		display(a, size);
		break;
	case 2:
		printf("select_sort: ");
		select_sort(a, size);
		display(a, size);
		break;
	case 3:
		printf("quick_sort: ");
		quick_sort(a, 0, size-1);
		display(a, size);
		break;
	case 4:
		printf("insert_sort: ");
		insert_sort(a, size);
		display(a, size);
		break;
	case 5:
		printf("shell_sort: ");
		shell_sort(a, size);
		display(a, size);
		break;
	case 6:
		printf("heap_sort: ");
		heap_sort(a, size-1);
		display(a, size);
		break;
	default:
		break;
	}
	return 0;
}
