#include <stdio.h>

int if_ugly_number(int n)
{
	while(n%2 == 0 && n != 0)
		n /= 2;
	while(n%3 == 0 && n != 0)
		n /= 3;
	while(n%5 == 0 && n != 0)
		n /=5;
	return (n==1? 1:0);
}

int get_ugly_number(int index)
{
	int tmp = 0;

	int count = 0;
	while(count < index)
	{
		if(if_ugly_number(tmp))
		{
			printf(" %d", tmp);
			count++;
		}
		tmp++;
	}
	puts("\n");
	return tmp;
}

int main(int argc, char *argv[])
{
	get_ugly_number(atoi(argv[1]));
	return 0;
}
