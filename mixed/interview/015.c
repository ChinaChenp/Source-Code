#include <stdio.h>

/*
** 从最右边开始计算位为1的个数
*/
int count_bit_1(int m)
{
    int count = 0;
    while(m)
    {
        if(m & 1)
            count++;
        m = m >> 1;
    }
    return count;
}

/*
** 从最左边开始计算位为1的个数
*/
int count_bit_2(int m)
{
    int count = 0;
    while(m)
    {
        count++;
        m = (m - 1)&m;
    }
    return count;
}

int main(int argc, char *argv[])
{
    int m = atoi(argv[1]);
    printf("%d--method one--->%d\n", m, count_bit_1(m));
    printf("%d--method two--->%d\n", m, count_bit_2(m));
    return 0;
}
