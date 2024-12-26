#include <iostream>

#include <cmath>

int main(int argc, char* argv[])
{
	long long available;
	std::cin>>available;

	const long long n = std::ceil(-1 + std::sqrt(4*available)/2);
	const auto needed = (n+1)*(n+1);

	std::cout<<(2*n+1)*(needed-available)<<'\n';
	
	return 0;
}

