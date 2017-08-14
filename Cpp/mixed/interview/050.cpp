#include <iostream>
using namespace std;

std::string slove(const char *str)
{
	unsigned char hash[256] = {0};
	string re;

	const char *front = str;
	while(*front != '\0')
		hash[*front++]++;

	for(int i=0; i<256; ++i)
	{
		if(hash[i] != 0)
			re += (unsigned char)i;
	}	
	return re;
}


int main(int argc, char* argv[])
{
	std::string re = slove(argv[1]);

	cout<<argv[1]<<"----->"<<re<<endl;
	return 0;
}

