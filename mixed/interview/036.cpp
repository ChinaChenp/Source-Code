#include <iostream>
using namespace std;

void str_permutation(char* str, char* start)
{

	if(*start == '\0')
		std::cout<<str<<std::endl;

    char *temp = start;
    while(*temp != '\0')
    {
        swap(*start, *temp);
        str_permutation(str, start+1);
        swap(*start, *temp);
        temp++;
    }
}


int main(void)
{
	char str[] = "123";
	str_permutation(str,str);
	return 0;
}
