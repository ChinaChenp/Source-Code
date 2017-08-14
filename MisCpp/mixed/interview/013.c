#include <stdio.h>

long total = 0;
long sum(int n)
{
	n&&(total = (n + sum(--n)));

	return total;
}

int main(int argc, char *argv[])
{
	int m = atoi(argv[1]);
	printf("1+2+3....+%d=%ld\n", m, sum(m));
	return 0;
}
