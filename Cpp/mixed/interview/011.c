#include <stdio.h>
#include <string.h>

#ifndef bool
typedef enum
{
	false,
	true,
}bool;
#endif

/*
** method one: loop twice
*/
bool str_in(const char *long_str, const char *short_str)
{
	int j,i;
	int long_len = strlen(long_str);
	int short_len = strlen(short_str);
	for(i=0; i<short_len; ++i)
	{
		for(j=0; j<long_len; j++)
		{
			if(long_str[j] == short_str[i])
				break;
		}
		if(j == long_len)
			return false;
	}
	return true;
}

/*
** method two: hash
*/
bool str_in_1(const char *long_str, const char *short_str)
{
	if(!long_str || !short_str)
		return -1;
	int i,total=0;
	int long_len = strlen(long_str);
	int short_len = strlen(short_str);
	
	int hash[26] = {0};
	int key = 0;
	for(i=0; i<short_len; ++i)
	{
		key = short_str[i] - 'A';
		if(hash[key] == 1)
			continue;
		hash[key] = 1;
		total++;
	}
	
	for(i=0; i<long_len; ++i)
	{
		key = long_str[i] - 'A';
		if(hash[key] == 0)
			continue;
		hash[key] = 0;
		total--;
	}
	
	return (total == 0?true:false);
}
int main(int argc, char *argv[])
{
	printf("--->%d\n", str_in("ABCDEFGHLMNOPQRS", "DCGSRQPO"));
	printf("--->%d\n", str_in("ABCDEFGHLMNOPQRS", "DCCGSRQPO"));
	printf("--->%d\n", str_in("ABCDEFGHLMNOPQRS", "DCCGGSRQPOz"));
	printf("--->%d\n", str_in_1("ABCDEFGHLMNOPQRS", "DCGSRQPO"));
	printf("--->%d\n", str_in_1("ABCDEFGHLMNOPQRS", "DCCGSRQPO"));
	printf("--->%d\n", str_in_1("ABCDEFGHLMNOPQRS", "DCCGGSRQPOz"));
	return 0;
}
