#include <iostream>
#include <string>
#include <sstream>

typedef long long Number;

std::string lastTwoDigitsFromFactorial(Number n)
{
	Number major = 0, minor = 0;

	if (n < 10)
	{
		switch(n)
		{
			case 0:
			case 1:
				minor = 1;
				break;
				
			case 2:
				minor = 2;
				break;
				
			case 3:
				minor = 6;
				break;
			
			case 4:
				major = 2;
				minor = 4;
				break;
			
			case 5:
			case 6:
			case 8:
				major = 2;
				break;
			
			case 7:
				major = 4;
				break;
			
			case 9:
				major = 8;
				break;
		}
	}
	
	std::stringstream ss;
	ss << major << " " << minor;
	return ss.str();
}

int main()
{
	std::ios_base::sync_with_stdio(0);
	
	Number n = 0, temp = 0;
	std::cin >> n;
	
	for(Number i = 0; i < n; ++i)
	{
		std::cin >> temp;
		std::cout << lastTwoDigitsFromFactorial(temp) << std::endl;
	}
	
	return 0;
}