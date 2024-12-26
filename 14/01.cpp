#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char* argv[])
{
	int x = 0, y = 0, max = 0;
	for(std::string instruction; std::getline(std::cin, instruction, ',');)
	{
		std::stringstream strm{instruction};
		char c;
		int step;
		strm>>c>>step;

		switch(c)
		{
			case 'U': y+=step; break;
			case 'D': y-=step; break;
			case 'L': x+=step; break;
			case 'R': x-=step; break;
		}
		max = std::max(max, y);
	}

	std::cout<<max;
	return 0;
}
