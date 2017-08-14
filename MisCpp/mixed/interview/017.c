#include <stdio.h>

static int hash[65536] = {0};
void hash_sort(int *array, int size)
{
    int i=0;
    for(; i<size; i++)
        hash[array[i]]++;
}

int main(int argc, char *argv[])
{
    int a[] = {1, 4, 1, 2, 5, 13, 4, 6, 8, 1000, 999, 9,};

    //sort
    int size = sizeof(a)/sizeof(int);
    hash_sort(&a, size);

    //print the array
    int i = 0;
    for(; i<65536 && size--; i++)
    {
        while(hash[i] != 0)
        {
            printf(" %d", i);
            hash[i]--;
        }
    }
    return 0;
}
