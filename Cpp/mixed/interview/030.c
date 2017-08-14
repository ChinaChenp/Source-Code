#include <stdio.h>
#include <string.h>

void str_proc(char *str)
{
	int len = strlen(str);
	char *start = str;
	char *end = str + len - 1;

	char temp;
	while(start < end)
	{
		if(*start >= 'a' && *start <= 'z')
		{	
			start++;
			continue;
		}

		if(*end >= 'A' && *end <= 'Z')
		{
			end--;
			continue;
		}

		{
			temp = *start;
			*start++ = *end;
			*end-- = temp;
		}
	}
}

int main(int argc, char *argv[])
{
	printf("%s----->", argv[1]);
	str_proc(argv[1]);
	printf("%s\n", argv[1]);
	return 0;
}
