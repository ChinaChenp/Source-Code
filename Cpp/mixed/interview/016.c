#include <stdio.h>

/*
** ��������@m�а�������@digit�ĸ���
*/
int count_digit_num(int m, int digit)
{
    int count = 0;
    while(m)
    {
        if(m%10 == digit)
            count++;
        m = m/10;
    }
    return count;
}

int count_digit_one(int m)
{
    int i=0;
    int count = 0;
    for(; i<=m; i++)
    {
        count += count_digit_num(i, 1);
    }
    return count;
}

int main(int argc, char *argv[])
{
    int m = atoi(argv[1]);
    printf("%d----->%d\n", m, count_digit_one(m));
}
