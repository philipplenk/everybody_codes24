#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
	struct point2d
	{
		int x, y;
	};
	
	std::vector<std::string> grid{std::istream_iterator<std::string>{std::cin},{}};
	const int width = grid[0].size();
	const int height = grid.size();

	point2d start{};
	for(int y=0; y<height; ++y)
		for(int x=0; x<width; ++x)
			if(grid[y][x]=='S')
				start = {x, y};

	std::vector<int> current_heights(width, 0);
	constexpr auto starting_altitude = 384400;
	current_heights[start.x] = starting_altitude;
	int steps = 0;
	
	for(;!std::ranges::all_of(current_heights,[](auto v){ return v<=0; }); ++steps)
	{
		const auto y = steps%height;
		std::vector<int> new_heights = current_heights;

		int max = -10;
		for(int i=0; i<width; ++i)
		{
			if(grid[y][i]=='#')
			{
				new_heights[i] = max = -10;
				continue;
			}
			const auto diff = grid[y][i]=='.'?-1:grid[y][i]=='+'?1:grid[y][i]=='-'?-2:-1;
			max = new_heights[i] = std::max({new_heights[i], max + diff, current_heights[i]});
		}
		max = -10;
		for(int i=width-1; i>=0; --i)
		{
			if(grid[y][i]=='#')
			{
				new_heights[i] = max = -10;
				continue;
			}
			const auto diff = grid[y][i]=='.'?-1:grid[y][i]=='+'?1:grid[y][i]=='-'?-2:-1;
			max = new_heights[i] = std::max({new_heights[i], max + diff, current_heights[i]});
		}
		if(steps==0) new_heights[start.x] = starting_altitude;

		const auto next_y = (steps+1)%height;
		for(int i=0; i<width; ++i)
		{
			if(grid[next_y][i]=='#')
			{
				current_heights[i] = 0;
				continue;
			}
			const auto diff = grid[next_y][i]=='.'?-1:grid[next_y][i]=='+'?1:grid[next_y][i]=='-'?-2:-1;
			current_heights[i] = new_heights[i] + diff;
		}
		for(auto& v: current_heights) v = v<=0?-10:v;
	}

	std::cout<<steps;
	return 0;
}
