#include <stdio.h>

int gcd(int x, int y)
{
	return ((!y) ? x: gcd(y, x%y));
}

int main(int argc, char *argv[])
{
	int m = atoi(argv[1]);
	int n = atoi(argv[2]);
	printf("%d--->%d<---%d\n", m, gcd(m, n), n);
}
