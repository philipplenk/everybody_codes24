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

	std::vector<bool> visited(width*height, false);
	std::vector<point2d> to_visit;
	to_visit.push_back({21,0});

	for(int step = 0; ; ++step)
	{
		std::vector<point2d> next;

		for(auto p: to_visit)
		{
			if(grid[p.y][p.x]=='H')
			{
				std::cout<<2*step;
				return 0;
			}

			const auto try_add = [&](point2d target)
			{
				if(target.x<0 || target.y<0 || target.x>=width || target.y>=height) return;
				if(grid[target.y][target.x]=='#') return;
				if(visited[target.y*width+target.x]) return;
				visited[target.y*width+target.x] = true;
				next.push_back(target);
			};

			try_add({p.x+1, p.y});
			try_add({p.x-1, p.y});
			try_add({p.x, p.y+1});
			try_add({p.x, p.y-1});
		}
		to_visit = std::move(next);
	}
	return 0;
}
