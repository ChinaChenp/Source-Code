#include <stdio.h>

int search_second_max(int *array, int size)
{
    int max = 0, second_max = 0;
    if(array[1] > array[0])
    {
        max = array[1];
        second_max = array[0];
    }
    else
    {
        max = array[0];
        second_max = array[1];
    }

    int i = 2;
    for(; i<size; ++i)
    {
        if(array[i] > max)
        {
            second_max = max;
            max = array[i];
        }
        else if(array[i] > second_max && array[i] < max)
        {
            second_max = array[i];
        }
    }
    return second_max;
}

int main()
{
    int a[] = {1, 65, 8, 4, 5, 65, 67, 9, 12, 35, 14, 67};
    printf("------>%d\n", search_second_max(a, sizeof(a)/sizeof(int)));
    return 0;
}
