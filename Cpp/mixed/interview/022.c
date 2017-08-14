#include <stdio.h>
#include <string.h>
char * delete_chars(char *str, char *del_chars)
{
	char hash[256] = {0};
	
	int i=0;
	int str_len = strlen(del_chars);
	for(; i<str_len; ++i)
	{
		if(hash[del_chars[i]] == 0)
			hash[del_chars[i]] = 1;
	}
	
	char *pos = str;
	char *sp = str;
	str_len = strlen(str);
	while(str_len--)
	{
		if(!hash[*pos])
		{
			*sp++ = *pos;
		}
		pos++;
	}
	*sp = '\0';
	return str;
}

int main(int argc, char *argv[])
{
	printf("%s--%s---->", argv[1], argv[2]);
	printf("%s\n", delete_chars(argv[1], argv[2]));
	return 0;
}

