#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *str_res(char *str)
{
	char t;
	char *begin = str;
	char *end = str + strlen(str) - 1;
	while(begin < end)
	{
		t = *begin;
		*begin++ = *end;
		*end-- = t;
	}
	return str;
}

char *int_to_str(int num)
{
	char *str = calloc(1, 16);
	char *s = str;
	while(num)
	{
		*str++ = num%10 + '0';
		num /= 10;
	}
	*str = '\0';
	return str_res(s);
}

char *str_compress(char *str)
{
	char tmp;
	char *fast = str;
	char *slow = str;
	char *r = str;
	
	int count = 0;
	while(*fast != '\0')
	{
		tmp = *fast++;
		while(*fast == tmp  && *fast != '\0')
			fast++;
		
		*r++ = *(fast-1);
		count = fast - slow;
		if(count != 1)
		{
			char *st = int_to_str(count);
			strcpy(r, st);
			r = r + strlen(st);
			free(st);
		}
		slow = fast;
	}
	*r = '\0';
	return str;
}

int main(int argc, char *argv[])
{
	printf("%s-------->", argv[1]);
	printf("%s\n", str_compress(argv[1]));
	return 0;
}

