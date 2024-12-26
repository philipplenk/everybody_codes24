#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
	std::vector<std::string> grid{std::istream_iterator<std::string>{std::cin},{}};
	const int width = grid[0].size();
	const int height = grid.size();

	struct point2d
	{
		int x, y;
	};

	std::vector<point2d> palms;
	for(int y=0; y<height; ++y)
		for(int x=0; x<width; ++x)
			if(grid[y][x]=='P')
				palms.push_back({x,y});


	std::vector<long> min(width*height, 0);
	std::vector<long> reached_by(width*height, 0);
	const auto fill = [&](point2d start)
	{
		std::vector<bool> seen(width*height, false);

		std::vector<point2d> current;
		current.push_back(start);
		seen[start.y*width + start.x] = true;
		for(int step=0; !current.empty() ; ++step)
		{
			std::vector<point2d> next;
			for(auto p: current)
			{
				min[p.y*width+p.x]+=step;
				if(grid[p.y][p.x]=='.')
					++reached_by[p.y*width+p.x];
				const auto try_add = [&](point2d p)
				{
					if(p.x<0 || p.y<0 || p.x>=width || p.y>=height) return;
					if(grid[p.y][p.x]=='#') return;
					if(seen[p.y*width+p.x]) return;
					seen[p.y*width+p.x] = true;
					next.push_back(p);
				};
				try_add({p.x-1, p.y});
				try_add({p.x+1, p.y});
				try_add({p.x, p.y-1});
				try_add({p.x, p.y+1});
			}
			current = std::move(next);
		}
	};

	for(auto p: palms)
		fill(p);

	for(int y=0; y<height; ++y)
		for(int x=0; x<width; ++x)
			if(reached_by[y*width+x]!=static_cast<int>(palms.size()))
				min[y*width+x] = std::numeric_limits<int>::max();

	std::cout<<*std::ranges::min_element(min);
	return 0;
}
