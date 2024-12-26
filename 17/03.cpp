#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <string_view>
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

	std::vector<point2d> stars;
	for(int y=0; y<height; ++y)
	{
		for(int x=0; x<width; ++x)
		{
			if(grid[y][x]=='*')
				stars.push_back(point2d{x,y});
		}
	}

	struct constellation_info
	{
		long brightness = 0;
		long size = 0;
	};

	const auto collect_next = [&]() -> constellation_info
	{
		std::vector<point2d> constellation;
		constellation.push_back(stars.back());
		stars.pop_back();

		long sum = 0;
		while(!stars.empty())
		{
			const auto it = std::ranges::min_element(stars, std::less<>{}, [&](auto star)
			{
				int min = std::numeric_limits<int>::max(); 
				for(const auto& other: constellation)
					if(auto dist = std::abs(other.x-star.x)+std::abs(other.y-star.y); dist<6)
						min = std::min(min, dist);
				return min;
			});

			int min = std::numeric_limits<int>::max(); 
			for(const auto& other: constellation)
				if(auto dist = std::abs(other.x-(*it).x)+std::abs(other.y-(*it).y); dist<6)
					min = std::min(min, dist);

			if(min==std::numeric_limits<int>::max())
				break;

			sum+=min;
			
			std::swap(*it, stars.back());
			constellation.push_back(stars.back());
			stars.pop_back();
		}

		return constellation_info(sum+constellation.size(), constellation.size());
	};

	std::vector<constellation_info> constellations;
	while(!stars.empty())
		constellations.push_back(collect_next());

	std::ranges::sort(constellations, std::greater<>{}, &constellation_info::brightness);
	std::cout<<constellations[0].brightness*constellations[1].brightness*constellations[2].brightness;

	return 0;
}
