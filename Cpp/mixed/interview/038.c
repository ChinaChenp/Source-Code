#include <stdio.h>

/*
** 找出两个数之间的素数的个数,并打印
** 注意:只能被1和本身整除的数
*/
int count_prime_number(int begin, int end)
{
    int i = begin, j;
    int count = 0;
    for(; i<end; ++i)
    {
        for(j=2; j<i; ++j)
        {
            if(i%j == 0)
                break;
        }
        if(j == i)
        {
            printf(" %d", i);
            count++;
        }
    }
    return count;
}

int main()
{
    printf("------->%d\n", count_prime_number(101, 200));
    return 0;
}
