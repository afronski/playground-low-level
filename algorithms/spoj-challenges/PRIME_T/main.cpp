#include <iostream>
#include <string>
#include <cmath>

typedef long Number;

std::string isPrime(Number n)
{
	if (n <= 1)
		return "NIE";

	if (n == 2)
		return "TAK";

	if (n % 2 == 0)
		return "NIE";

	Number m = std::sqrt(n);

	for (Number i = 3; i <= m; i += 2)
	{
		if (n % i == 0)
		{
			return "NIE";
		}
	}

	return "TAK";
}

int main()
{
	std::ios_base::sync_with_stdio(0);

	Number n = 0, temp = 0;
	std::cin >> n;

	for(Number i = 0; i < n; ++i)
	{
		std::cin >> temp;
		std::cout << isPrime(temp) << std::endl;
	}

	return 0;
}