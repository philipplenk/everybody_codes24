#include <algorithm>
#include <array>
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

	std::vector<point2d> to_visit;
	to_visit.push_back(start);

	std::array<std::vector<int>,4> heights_from;
	for(auto& heights: heights_from) heights.resize(width*height, 0);
	heights_from[0][start.y*width+start.x] = 1001;
	heights_from[1][start.y*width+start.x] = 1001;
	heights_from[2][start.y*width+start.x] = 1001;
	heights_from[3][start.y*width+start.x] = 1001;

	for(int i=0; i<100; ++i)
	{
		std::array<std::vector<int>,4> new_heights_from;
		for(auto& heights: new_heights_from) heights.resize(width*height, 0);
		std::vector<point2d> next_to_visit;

		const auto try_add = [&](point2d from, point2d p, int direction)
		{
			if(p.x<0 || p.y<0 || p.x>=width || p.y>=height) return;
			if(grid[p.y][p.x]=='#' || grid[p.y][p.x]=='S') return;
			const auto forbidden = direction==0?1:direction==1?0:direction==2?3:2;
			int max_from = 0;
			for(int i=0; i<4; ++i)
			{
				if(i==forbidden) continue;
				max_from = std::max(max_from, heights_from[i][from.y*width+from.x]);
			}
			if(max_from==0) return;
			if(new_heights_from[direction][p.y*width+p.x]==0)
				next_to_visit.push_back(p);
			
			const auto diff = grid[from.y][from.x]=='.'?-1:grid[from.y][from.x]=='+'?1:grid[from.y][from.x]=='-'?-2:0;
			new_heights_from[direction][p.y*width+p.x] = std::max(new_heights_from[direction][p.y*width+p.x], max_from+diff);
		};
		
		for(const auto& p: to_visit)
		{
			try_add(p, {p.x-1, p.y}, 0);
			try_add(p, {p.x+1, p.y}, 1);
			try_add(p, {p.x, p.y+1}, 2);
			try_add(p, {p.x, p.y-1}, 3);
		}

		to_visit = std::move(next_to_visit);
		heights_from = std::move(new_heights_from);
	}

	std::cout<<std::max({*std::ranges::max_element(heights_from[0]),*std::ranges::max_element(heights_from[1]),*std::ranges::max_element(heights_from[2]), *std::ranges::max_element(heights_from[3])});
	return 0;
}
