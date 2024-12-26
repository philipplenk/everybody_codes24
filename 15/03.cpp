#include <bit>
#include <iostream>
#include <iterator>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

#include <cstdint>

int main(int argc, char* argv[])
{
	std::vector<std::string> grid{std::istream_iterator<std::string>{std::cin},{}};
	const int width = grid[0].size();
	const int height = grid.size();

	std::uint32_t all = 0;
	for(int y=0; y<height; ++y)
		for(int x=0; x<width; ++x)
			if(std::isalpha(grid[y][x]))
				all|=(1u<<(grid[y][x]-'A'));

	std::cerr<<std::popcount(all)<<'\n';
	const auto to_collect = std::popcount(all);

	struct point2d
	{
		int x, y;
	};

	struct waypoint
	{
		point2d pos{};
		int distance{0};
		std::uint32_t collected{0};

		bool operator<(const waypoint& other) const
		{
			const auto collected_sum = std::popcount(collected);
			const auto other_collected_sum = std::popcount(other.collected);

			if(other.distance+(std::abs(other.pos.x-127)+other.pos.y)<distance+(std::abs(pos.x-127)+pos.y)) return true;
			if(other.distance+(std::abs(other.pos.x-127)+other.pos.y)>distance+(std::abs(pos.x-127)+pos.y)) return false;
			if(other_collected_sum>collected_sum) return true;
			if(other_collected_sum<collected_sum) return false;
			return other.distance<distance;
		}
	};

	point2d start{127,0};
	std::priority_queue<waypoint> to_visit;
	to_visit.push({start, 0, 0});

	std::vector<std::unordered_set<std::uint32_t>> visited(width*height);

	int max_collected = 0;
	while(!to_visit.empty())
	{
		auto next = to_visit.top();
		to_visit.pop();

		if(std::isalpha(grid[next.pos.y][next.pos.x]))
			next.collected|=(1u<<(grid[next.pos.y][next.pos.x]-'A'));

		if(next.pos.x==start.x && next.pos.y==start.y && std::popcount(next.collected)==to_collect)
		{
			std::cout<<next.distance;
			break;
		}

		if(std::popcount(next.collected)>max_collected)
			std::cerr<<(max_collected = std::popcount(next.collected))<<'\n';
		
		const auto try_add = [&](point2d target)
		{
			if(target.x<0 || target.y<0 || target.x>=width || target.y>=height) return;
			if(grid[target.y][target.x]=='#') return;
			if(grid[target.y][target.x]=='~') return;
			if(visited[target.y*width+target.x].contains(next.collected)) return;
			visited[target.y*width+target.x].insert(next.collected);
			to_visit.push({target, next.distance+1, next.collected});
		};
		
		try_add({next.pos.x+1, next.pos.y});
		try_add({next.pos.x-1, next.pos.y});
		try_add({next.pos.x, next.pos.y+1});
		try_add({next.pos.x, next.pos.y-1});
	}
	
	return 0;
}
