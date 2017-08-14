#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * left_one_step(char *s, int size)
{
	char c = s[0];
	int i=0;
	for( ;i<size; ++i)
		s[i] = s[i+1];
	s[--i] = c;
	return s;
}

char * left_n_step(char *s, int size, int n)
{
	char *re = s;
	int m = n%size;
	while(m--)
	{
		re = left_one_step(re, size);
	}
	return re;
}

int main(int argc, char *argv[])
{
	char *str = strdup(argv[1]);
	printf("%s--left:%d--->%s\n", argv[1], atoi(argv[2]), left_n_step(str, strlen(str), atoi(argv[2])));
	free(str);

	return 0;
}
