#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include <cstddef>

int main(int argc, char* argv[])
{
	std::vector<std::string> grid{std::istream_iterator<std::string>{std::cin},{}};
	const auto width = grid[0].size();
	const auto height = grid.size();

	struct point2d
	{
		int x, y;
	};

	std::vector<point2d> sources(3), targets;
	for(std::size_t y=0; y<height; ++y)
	{
		for(std::size_t x=0; x<width; ++x)
		{
			if(std::isupper(grid[y][x]))
			{
				if(grid[y][x]=='T')
					targets.push_back(point2d(x,y));
				else
					sources[grid[y][x]-'A']= point2d(x,y);
			}
		}
	}

	int result = 0;
	for(auto target: targets)
	{
		int best = 0, cost = 100;
		for(std::size_t i=0; i<sources.size(); ++i)
		{
			const auto dist_y = target.y - sources[i].y;
			const auto dist_x = target.x - sources[i].x;
			if((dist_x - dist_y)%3!=0) continue;
			const auto required_power = (dist_x - dist_y)/3;

			if(required_power<cost)
			{
				cost = required_power;
				best = i;
			}
		}
		result+=(best+1)*cost;
	}
	std::cout<<result;
	return 0;
}
