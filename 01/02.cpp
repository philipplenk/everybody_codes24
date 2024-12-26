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
	
	for(char first, second; std::cin>>first>>second;)
	{
		if(first=='x' || second=='x')
			result+=value(first)+value(second);
		else
			result+=value(first)+value(second)+2;
	}
	std::cout<<result;
}
