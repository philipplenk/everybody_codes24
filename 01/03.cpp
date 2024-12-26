#include <iostream>

int main(int argc, char* argv[])
{
	int result = 0;

	const auto value = [](auto c)
	{
		if(c=='A') return 0;
		if(c=='B') return 1;
		if(c=='C') return 3;
		if(c=='D') return 5;

		return 0;
	};
	
	for(char first, second, third; std::cin>>first>>second>>third;)
	{
		const auto count = (first!='x')+(second!='x')+(third!='x');
		result+=value(first)+value(second)+value(third)+(count==3?6:count==2?2:0);
	}

	std::cout<<result;
}
