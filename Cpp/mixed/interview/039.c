#include <stdio.h>
#include <string.h>

#define MAX_LEN 15  //255.255.255.255
#define MIN_LEN  7  //0.0.0.0

int str_to_int(const char *begin, const char *end)
{
    int total = 0;
    const char *s = begin;
    while(s < end)
    {
        total = 10*total + (*s - '0');
        s++;
    }
    printf("total=%d\n", total);
    return total;
}

/*
** ip合法性检查
** (1) 字符串只含有数字和'.'
** (2) 长度在7-15之间(0.0.0.0--255.255.255.255)
** (3) 每个数字在0-255之间
** (4) '.'号不能超过3个,且不能连续
*/
int check_ip(const char *str)
{
    int len = strlen(str);
    if(!str || len > MAX_LEN || len < MIN_LEN)
        return 0;

    const char *slow = str, *fast = str;
    int count_dot = 0, tmp;
    while(*fast != '\0')
    {
        if(*fast != '.' && (*fast < '0' || *fast > '9'))
            return 0;

        while(*fast != '.')
        {
            if(*fast == '\0')
                break;
            fast++;
        }

        if(*fast == '.')
        {
            if(++count_dot > 3) //.数量大于3个
                return 0;
        }

        if(*fast == '.' && *slow == '.')  //两个.挨着
            return 0;

        tmp = str_to_int(slow, fast);
        if(tmp < 0 || tmp > 255)
            return 0;

        slow = ++fast;
    }
    return 1;
}

int main()
{
    char str[] = "01.16";
    //char str[] = " 01.168.1.2";
    //char str[] = "01.168..2";
    //char str[] = "192.168.2.1000";
    printf("-------->%d\n", check_ip(str));
}
