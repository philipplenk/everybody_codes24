#include <iostream>

int main(int argc, char* argv[])
{
	int sum = 0;
	for(int target; std::cin>>target;)
	{
		sum+=target/10;
		target%=10;
		sum+=target/5;
		target%=5;
		sum+=target/3;
		target%=3;
		sum+=target;
	}

	std::cout<<sum;
	return 0;
}
