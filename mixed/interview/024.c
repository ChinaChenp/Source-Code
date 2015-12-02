#include <stdio.h>
#include <string.h>

int count_max_digit_str(char *output_str,char *input_str)
{
    char *fast = input_str;
    char *slow = input_str;

    int len = strlen(input_str);
    int i = 0, max_digit_len = 0, tmp = 0;
    for(; i<len; ++i)
    {
        if(input_str[i] < '0' || input_str[i] > '9')
        {
            fast++;
            slow++;
            continue;
        }

        fast++;
        if( *fast < '0' || *fast > '9')
        {
            tmp = fast - slow;
            if(tmp > max_digit_len)
            {
                max_digit_len = tmp;
                memcpy(output_str, slow, tmp);
            }
            tmp = 0;
            slow = fast;
        }
    }
    output_str[max_digit_len] = '\0';

    return max_digit_len;
}

int main(int argc, char *argv[])
{
    char re[128] = "";
    int max = count_max_digit_str(re, argv[1]);
    printf("%s--%d-->%s\n", argv[1], max, re);
}
