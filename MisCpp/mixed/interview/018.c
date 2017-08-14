#include <stdio.h>

void print(int start, int end)
{
    printf(" [%d--%d]", start, end);
	printf("\n");
}

void get_continue_array(int n)
{
    int start = 1;
    int end = 2;
    int mid = (n+1)/2; /*循环管的终点*/

    int sum = start + end;
    while(start < mid)
    {
        if(sum < n)
        {
            /*
            ** 和不够,尾部右移,并叠加到@sum中
            */
            sum += ++end;
        }
        else if(sum > n)
        {
            /*
            ** 和超越了需要的值,说明@start和@end之间的序列
            ** 不可能构成需要的值舍去头部值,头部右移
            */
            sum -= start++;
        }
        else
        {
            print(start, end);
            sum -= start++;
        }
    }


}
int main(int argc, char *argv[])
{
    int m = atoi(argv[1]);
    get_continue_array(m);
    return 0;
}
