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
				min = std::min(min, std::abs(other.x-star.x)+std::abs(other.y-star.y));
			return min;
		});

		int min = std::numeric_limits<int>::max(); 
		for(const auto& other: constellation)
			min = std::min(min, std::abs(other.x-(*it).x)+std::abs(other.y-(*it).y));

		sum+=min;
		
		std::swap(*it, stars.back());
		constellation.push_back(stars.back());
		stars.pop_back();
	}

	std::cout<<sum+constellation.size();
	return 0;
}
