#include <stdio.h>
#include <string.h>


char *str_chr(const char *str, char c, int num)
{
	int len = strlen(str);
	char *re = str;
	int i=0; 
	for(; i<len; i++)
	{
		if(i == num)
		{
			re++;
			continue;
		}
		if(*re == c)
			return re;
		re++;
	}
	return NULL;
}

char find_once_char_in_str(const char *str)
{
	int i=0;
	int len = strlen(str);

	for(; i<len; ++i)
	{
		if(str_chr(str, str[i], i) == NULL)
			return str[i];
	}
	return 0;
}

char find_once_char_in_str_hash(const char *str)
{
	char hash[256] = {0};
	int len = strlen(str);

	int temp = len;
	while(temp--)
	{
		if(hash[*str] == 0)
			hash[*str++]++;
		else if(hash[*str] == 1)
			hash[*str++]--;
	}
	while(len--)
	{
		if(hash[*str] == 1)
			return *str;
		str--;
	}
	return 0;
}
int main()
{
	char *str = "aabadccdxjebff77xe";
	printf("---> %c\n", find_once_char_in_str(str));
	printf("---> %c\n", find_once_char_in_str_hash(str));
	return 0;
}
