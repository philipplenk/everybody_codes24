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
	
	std::vector<std::vector<point2d>> reorder_grid(height, std::vector<point2d>(width)); 
	for(int y=0; y<height; ++y)
		for(int x=0; x<width; ++x)
			reorder_grid[y][x] = point2d(x,y);

	const auto apply = [&](auto& grid)
	{
		int rotation_index = 0;
		for(int y=1; y<height-1; ++y)
		{
			for(int x=1; x<width-1; ++x)
			{
				std::array<std::decay_t<decltype(grid[0][0])>, 8> to_rotate{};
				for(std::size_t i=0; i<to_rotate.size(); ++i)
					to_rotate[i] = grid[y+offsets[i].y][x+offsets[i].x];
				
				if(rotations[rotation_index++]=='L')
					std::rotate(to_rotate.begin(), to_rotate.begin()+1, to_rotate.end());
				else
					std::rotate(to_rotate.rbegin(), to_rotate.rbegin()+1, to_rotate.rend());

				rotation_index%=static_cast<int>(rotations.size());

				for(std::size_t i=0; i<to_rotate.size(); ++i)
					grid[y+offsets[i].y][x+offsets[i].x] = to_rotate[i];
			}
		}
	};

	int steps = 4096;
	for(int i=0; i<steps; ++i)
		apply(reorder_grid);

	const auto bound = 1048576000;
	for(int i=0; i<bound; i+=steps)
	{
		auto new_grid = grid;
		for(int y=0; y<height; ++y)
		{
			for(int x=0; x<width; ++x)
			{
				const auto target = reorder_grid[y][x];
				new_grid[y][x] = grid[target.y][target.x];
			}
		}
		grid = std::move(new_grid);
	}

	int start_x = 0, start_y = 0, end_x = 0;
	for(int y=0; y<height; ++y)
	{
		for(int x=0; x<width; ++x)
		{
			if(grid[y][x]=='<')
				end_x = x;

			if(grid[y][x]=='>')
			{
				start_x = x;
				start_y = y;
			}
		}
	}

	for(int x=start_x+1; x<end_x; ++x)
		std::cout<<grid[start_y][x];

	return 0;
}
