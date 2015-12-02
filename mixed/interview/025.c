#include <stdio.h>
#include <string.h>

int count_max_decrease_array(int *array, int size, int *output_array)
{
    int *fast = array;
    int *slow = array;
	int temp = 0;
    int i = 0, max_digit_len = 0, tmp_len = 0;
    for(; i<size; ++i)
    {
        if(*fast >= *slow)
		{
            slow = fast++;
            continue;
        }

        temp = *fast++;
        if(*fast >= temp || i == (size-1))
        {
            tmp_len = (fast - slow);
            if(tmp_len > max_digit_len)
            {
                max_digit_len = tmp_len;
                memcpy(output_array, slow, tmp_len*sizeof(int));
            }
            tmp_len = 0;
            slow = fast;
        }
    }
    return max_digit_len;
}

void print(int *array, int max)
{
	printf("max = %d\n", max);
	int i=0;
	for(; i<max; ++i)
		printf(" %d", array[i]);
	printf("\n");
}

int main(int argc, char *argv[])
{
    //int in[]={1, 2, 3, 4, 5,};
    int in[]={9, 4, 3, 2,100, 99, 88, 77, 66, 6, 5, 4, 8, 3, 2};
	int out[128]={0};
    int max = count_max_decrease_array(in, sizeof(in)/sizeof(int), out);
	print(out, max);	
	return 0;
}
