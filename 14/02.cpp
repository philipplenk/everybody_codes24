#include <iostream>
#include <set>
#include <sstream>
#include <string>

struct point3d
{
	int x, y, z;
	friend auto operator<=>(const point3d&, const point3d&) = default;
};

int main(int argc, char* argv[])
{
	std::set<point3d> seen;
	for(std::string line; std::getline(std::cin, line); )
	{
		std::stringstream linestrm{line};
		int x = 0, y = 0, z = 0;
		for(std::string instruction; std::getline(linestrm, instruction, ',');)
		{
			std::stringstream strm{instruction};
			char c;
			int step;
			strm>>c>>step;

			switch(c)
			{
				case 'U': for(int i=0; i<step; ++i) { y+=1; seen.insert({x,y,z}); }  break;
				case 'D': for(int i=0; i<step; ++i) { y-=1; seen.insert({x,y,z}); }  break;
				case 'L': for(int i=0; i<step; ++i) { x+=1; seen.insert({x,y,z}); }  break;
				case 'R': for(int i=0; i<step; ++i) { x-=1; seen.insert({x,y,z}); }  break;
				case 'F': for(int i=0; i<step; ++i) { z+=1; seen.insert({x,y,z}); }  break;
				case 'B': for(int i=0; i<step; ++i) { z-=1; seen.insert({x,y,z}); }  break;
			}
		}
	}

	std::cout<<seen.size();
	return 0;
}
