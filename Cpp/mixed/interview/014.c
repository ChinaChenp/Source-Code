#include <stdio.h>

int get_n(int n)
{
	if(n == 0)
		return 0;
	else if(n <= 1)
		return 1;
	else
	{
		return (get_n(n-1) + get_n(n-2));
	}
}

int main(int argc, char *argv[])
{
	int m = atoi(argv[1]);
	printf("%d----->%d\n", m, get_n(m));
	return 0;
}
