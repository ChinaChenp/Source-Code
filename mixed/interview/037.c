#include <stdio.h>

int double_equal(double a, double b)
{
	double diff = a-b;
	if(diff > -0.000001 && diff < 0.000001)
		return 1;
	else
		return 0;
}

double Power(double base, int exp)
{
	if(double_equal(base, 0.0) && (exp <= 0))
		return 0.0;

	int ads_exp = (exp > 0)?exp:-exp;

	int i = 0;
	double result = 1.0;
	for(; i<ads_exp; ++i)
	{
		result *= base;
	}

	return ((exp > 0)? result:1.0/result);
}

int main()
{
	double base = 0.0; int exp = 2;
	printf("%f^%d-->%f\n", base, exp, Power(base, exp));
	base = 0.0; exp = 0;
	printf("%f^%d-->%f\n", base, exp, Power(base, exp));
	base = 3.0; exp = -3;
	printf("%f^%d-->%f\n", base, exp, Power(base, exp));
	base = 3.0; exp = 100;
	printf("%f^%d-->%f\n", base, exp, Power(base, exp));
	return 0;
}
