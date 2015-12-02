#include <stdio.h>
#include <string.h>
#include <assert.h>

char * revstr(char *str)
{
	char *h = str;
	char *q = str + strlen(str)-1;
	char *r = str;
	
	assert(str != NULL);

	char c;
	while(h < q)
	{
#if 0
		c = *h;
		*h++ = *q;
		*q-- = c;
#else
		*h ^= *q;
		*q ^= *h;
		*h++ ^= *q--;
#endif
	}
	return r; 
}

int main(int argc, char *argv[])
{
	printf("%s-->%s\n", argv[1], revstr(argv[1]));

	return 0;
}
