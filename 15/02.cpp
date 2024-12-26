#include <array>
#include <bit>
#include <iostream>
#include <iterator>
#include <queue>
#include <string>
#include <vector>

#include <cstdint>

int main(int argc, char* argv[])
{
	std::vector<std::string> grid{std::istream_iterator<std::string>{std::cin},{}};
	const int width = grid[0].size();
	const int height = grid.size();

	struct point2d
	{
		int x, y;
	};

	[[maybe_unused]] const auto shortest = [&](point2d from, point2d to)
	{
		std::vector<bool> visited(width*height, false);
		std::vector<point2d> to_visit;
		to_visit.push_back(from);

		for(int step = 0; ; ++step)
		{
			std::vector<point2d> next;

			for(auto p: to_visit)
			{
				if(p.x==to.x && p.y==to.y)
				{
					return step;
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
	};

	struct waypoint
	{
		point2d pos{};
		int distance{0};
		std::uint16_t collected{0};

		bool operator<(const waypoint& other) const
		{
			const auto collected_sum = std::popcount(collected);
			const auto other_collected_sum = std::popcount(other.collected);

			if(other.distance+(std::abs(other.pos.x-42)+other.pos.y)<distance+(std::abs(pos.x-42)+pos.y)) return true;
			if(other.distance+(std::abs(other.pos.x-42)+other.pos.y)>distance+(std::abs(pos.x-42)+pos.y)) return false;
			if(other_collected_sum>collected_sum) return true;
			if(other_collected_sum<collected_sum) return false;
			return other.distance<distance;
		}
	};

	point2d start{42,0};
	const auto to_collect = 5;
	std::priority_queue<waypoint> to_visit;
	to_visit.push({start, 0, 0});

	std::array<std::vector<bool>,1<<7> visited{};
	for(auto& v: visited) v.resize(width*height, false);
	
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
		
		const auto try_add = [&](point2d target)
		{
			if(target.x<0 || target.y<0 || target.x>=width || target.y>=height) return;
			if(grid[target.y][target.x]=='#') return;
			if(grid[target.y][target.x]=='~') return;
			if(visited[next.collected][target.y*width+target.x]) return;
			visited[next.collected][target.y*width+target.x] = true;
			to_visit.push({target, next.distance+1, next.collected});
		};
		
		try_add({next.pos.x+1, next.pos.y});
		try_add({next.pos.x-1, next.pos.y});
		try_add({next.pos.x, next.pos.y+1});
		try_add({next.pos.x, next.pos.y-1});
	}
	
	return 0;
}
