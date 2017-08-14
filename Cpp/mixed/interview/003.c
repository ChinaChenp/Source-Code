#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *rev_str_word(char *str)
{
	char *start = str;
	char *end = str + strlen(str);
	char *space = end;
	
	char *re = strdup(str);
	char *temp = re;

	/*@space point to last space*/
	while((space = strrchr(str, ' ')) != NULL)
	{
		int len = end-space;
		memcpy(re, space, len);
		re += len;
		end = space;
		*space = '\0';
	}

	/*copy last str*/
	if(strlen(start) != 0)
	{
		*re = ' ';
		memcpy(++re, start, strlen(start));
	}
	return temp;
}

void rev_str(char *begin, char *end)
{
	char ch;
	while(begin < end)
	{
		ch = *begin;
		*begin++  = *end;
		*end-- = ch;
	}
}

char *rev_str_word_1(char *str)
{
	if(!str)
		return NULL;

	int len = strlen(str);
	rev_str(str, str+len-1);

	char *fast = str;
	char *slow = str;
	while(*fast != '\0')
	{
		while(*fast != ' ')
		{
			fast++;
			if(*fast == '\0')
				break;
			continue;
		}
		rev_str(slow, fast - 1);
		slow = ++fast;
	}
	return str;
}


int main(int argc, char *argv[])
{
	printf("%s---->", argv[1]);
	char *str = rev_str_word(argv[1]);
	//char *str = rev_str_word_1(argv[1]);
	printf("%s\n",str);
	return 0;
}

