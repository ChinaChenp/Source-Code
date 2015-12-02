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
    int mid = (n+1)/2; /*ѭ���ܵ��յ�*/

    int sum = start + end;
    while(start < mid)
    {
        if(sum < n)
        {
            /*
            ** �Ͳ���,β������,�����ӵ�@sum��
            */
            sum += ++end;
        }
        else if(sum > n)
        {
            /*
            ** �ͳ�Խ����Ҫ��ֵ,˵��@start��@end֮�������
            ** �����ܹ�����Ҫ��ֵ��ȥͷ��ֵ,ͷ������
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
