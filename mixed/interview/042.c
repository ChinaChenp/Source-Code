#include <stdio.h>
#include <string.h>

int is_rotate_str(char *des, char *src)
{
	int len = strlen(des);
	
	int i = 0, j;
	char tmp;
	for(; i<len; ++i)
	{
		tmp = des[0];
		for(j=0; j<len; ++j)
			des[j] = des[j+1];
		des[len - 1] = tmp;
		
		if(!strncmp(des, src, len))
			return 1;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	printf("%s---%s-->", argv[1], argv[2]);
	printf("%d\n", is_rotate_str(argv[1], argv[2]));
}
