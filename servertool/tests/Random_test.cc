#include <iostream>
#include "Random.h"

/// test random

int main()
{
	basetool::Random random;

	const int test_base = 5000 * 10000;
	// int
	int section0_100 = 0;
	int section100_200 = 0;
	int section200_300 = 0;
	int section300_400 = 0;
	int section400_500 = 0;

	uint32_t tmp = 0;
	for(int i = 0; i < test_base; ++i)
	{
		tmp = random.rangeInt(500);
		if(tmp > 0 && tmp < 100)
			section0_100++;
		else if(tmp >=100 && tmp < 200)
			section100_200++;
		else if(tmp >= 200 && tmp < 300)
			section200_300++;
		else if(tmp >= 300 && tmp < 400)
			section300_400++;
		else
			section400_500++;

		if(section0_100 < 100)
			std::cout << random.rangeInt(500) << " ";
	}
	std::cout << std::endl;
	std::cout<<"(0   --- 100) --> " << section0_100 << "\n"
					 <<"[100 --- 200) --> " << section100_200 << "\n"
					 <<"[200 --- 300) --> " << section200_300 << "\n"
					 <<"[300 --- 400) --> " << section300_400 << "\n"
					 <<"[400 --- 500) --> " << section400_500 << "\n"
					 << std::endl;
	
	// bool
	int bool_0 = 0;
	int bool_1 = 0;
	for(int i = 0; i < test_base; ++i)
	{
		if(random.rangeBool())
			bool_1++;
		else
			bool_0++;
		
		if(bool_1 < 100 )
			std::cout << random.rangeBool() << " ";
	}
	std::cout << std::endl;

	std::cout << "count bool 0 " << bool_0 << "\n"
						<< "count bool 1 " << bool_1 << "\n";

	// double
	section0_100 = 0;
	section100_200 = 0;
	section200_300 = 0;
	section300_400 = 0;
	section400_500 = 0;
	double ret = 0.0;
	for(int i = 0; i < test_base; ++i)
	{
		ret = random.rangeDouble(500);
		if(ret > 0 && ret < 100)
			section0_100++;
		else if(ret >=100 && ret < 200)
			section100_200++;
		else if(ret >= 200 && ret < 300)
			section200_300++;
		else if(ret >= 300 && ret < 400)
			section300_400++;
		else
			section400_500++;
		if(section0_100 < 100)
			std::cout << random.rangeDouble(500) << " ";
	}
	std::cout << std::endl;
	std::cout<<"(0   --- 100) --> " << section0_100 << "\n"
					 <<"[100 --- 200) --> " << section100_200 << "\n"
					 <<"[200 --- 300) --> " << section200_300 << "\n"
					 <<"[300 --- 400) --> " << section300_400 << "\n"
					 <<"[400 --- 500) --> " << section400_500 << "\n"
					 << std::endl;
	return 0;
}
