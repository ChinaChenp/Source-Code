#include <stdio.h>
#include <string.h>

int sub_str_count(const char *str, const char *sub_str)
{
	int str_len = strlen(str);
	int sub_str_len = strlen(sub_str);

	int count = 0;
	int times = str_len - sub_str_len + 1;
	while(times--)
	{
		if(!strncmp(str, sub_str, sub_str_len))
			count++;
		str++;
	}
	return count;
}

int main(int argc, char *argv[])
{
	printf("%s----%s--->%d\n", argv[1], argv[2], sub_str_count(argv[1], argv[2]));
	return 0;
}
