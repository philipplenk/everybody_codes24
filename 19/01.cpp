#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include <cstddef>

struct point2d
{
	int x, y;
};

struct vec2d
{
	int x, y;
};

int main(int argc, char* argv[])
{
	constexpr std::array offsets = 
	{
		vec2d{0, -1},
		vec2d{1, -1},
		vec2d{1, 0},
		vec2d{1, 1},
		vec2d{0, 1},
		vec2d{-1, 1},
		vec2d{-1,0},
		vec2d{-1,-1}
	};

	std::string rotations;
	std::cin>>rotations>>std::ws;

	std::vector<std::string> grid{std::istream_iterator<std::string>{std::cin},{}};
	const int width = grid[0].size();
	const int height = grid.size();

	point2d start{}, end{};
	for(int y=0; y<height; ++y)
	{
		for(int x=0; x<width; ++x)
		{
			if(grid[y][x]=='<')
				end = {x,y};
			if(grid[y][x]=='>')
				start = {x,y};
		}
	}

	for(;;)
	{
		int rotation_index = 0;
		for(int y=1; y<height-1; ++y)
		{
			for(int x=1; x<width-1; ++x)
			{
				std::string to_rotate;
				for(const auto& offset: offsets)
					to_rotate+=grid[y+offset.y][x+offset.x];

				if(rotations[rotation_index++]=='L')
					std::rotate(to_rotate.begin(), to_rotate.begin()+1, to_rotate.end());
				else
					std::rotate(to_rotate.rbegin(), to_rotate.rbegin()+1, to_rotate.rend());

				rotation_index%=static_cast<int>(rotations.size());

				for(std::size_t i=0; i<to_rotate.size(); ++i)
					grid[y+offsets[i].y][x+offsets[i].x] = to_rotate[i];

				for(std::size_t i=0; i<to_rotate.size(); ++i)
				{
					if(to_rotate[i]=='<')
						end = {x+offsets[i].x, y+offsets[i].y};
					if(to_rotate[i]=='>')
						start = {x+offsets[i].x, y+offsets[i].y};
				}

				if(start.y==end.y && start.x<end.x)
				{
					for(int x=start.x+1; x<end.x; ++x)
						std::cout<<grid[start.y][x];
					return 0;
				}
			}
		}
	}
	
	return 0;
}
