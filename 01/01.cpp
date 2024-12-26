#include <iostream>

int main(int argc, char* argv[])
{
	int result = 0;
	for(char c; std::cin>>c; result+=c=='B'?1:c=='C'?3:0);
	std::cout<<result;
}
