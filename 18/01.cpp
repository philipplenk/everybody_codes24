#include <iostream>
#include <iterator>
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

	int palms = 0;
	for(int y=0; y<height; ++y)
		for(int x=0; x<width; ++x)
			palms+=grid[y][x]=='P';

	std::vector<bool> seen(width*height, false);

	int found = 0;
	std::vector<point2d> current;
	current.push_back({0,1});
	seen[width] = true;
	for(int step=0; ; ++step)
	{
		std::vector<point2d> next;
		for(auto p: current)
		{
			if(grid[p.y][p.x]=='P') ++found;
			if(found==palms)
			{
				std::cout<<step;
				return 0;
			}

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
	return 0;
}
