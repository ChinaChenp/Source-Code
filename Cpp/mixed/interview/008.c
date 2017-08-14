#include <stdio.h>

int str_to_int(const char *str)
{
	if(!str)
		return 0;

	char *re = str;
	while(*re == ' ')
		re++;
	if(*re == '-' || *re == '+')
		re++;

	int sum = 0;
	while(*re != '\0')
	{
		if(*re >= '0' && *re <= '9')
		{
			sum = 10*sum + (*re - '0');
			re++;
			continue;
		}
		break;
	}
	return ((*str == '-')?-sum:sum);
}

int main(int argc, char *argv[])
{
	printf("%s--str_to_int-->%d\n", argv[1], str_to_int(argv[1]));
	printf("%s--atoi-------->%d\n", argv[1], atoi(argv[1]));
	return 0;
}
