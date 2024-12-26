#include <array>
#include <iostream>
#include <iterator>
#include <queue>
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

	struct waypoint
	{
		point2d position;
		int steps = 0, altitude = 10001, collected = 0, forbidden = -1;
	};

	const auto compare = [&](const waypoint& lhs, const waypoint& rhs)
	{
		if(lhs.steps>rhs.steps) return true;
		if(lhs.steps<rhs.steps) return false;

		if(lhs.collected<rhs.collected) return true;
		if(lhs.collected>rhs.collected) return false;

		if(lhs.altitude<rhs.altitude) return true;
		if(lhs.altitude>rhs.altitude) return false;

		return std::abs(lhs.position.x-start.x)+std::abs(lhs.position.y-start.y) > std::abs(rhs.position.x-start.x)+std::abs(rhs.position.y-start.y);
	};

	std::priority_queue<waypoint, std::vector<waypoint>, decltype(compare)> to_visit(compare);
	to_visit.push({start, 0, 10000, 0, -1});

	std::array<std::array<std::vector<int>,4>,4> max_height_with_from;
	for(auto& max_height_with: max_height_with_from)
		for(auto& heights: max_height_with) heights.resize(width*height, 0);

	while(!to_visit.empty())
	{
		const auto next = to_visit.top();
		to_visit.pop();
		if(next.position.x==start.x && next.position.y==start.y && next.collected==3 && next.altitude>=10000)
		{
			std::cout<<next.steps;
			return 0;
		}

		const auto try_add = [&](point2d p, int direction)
		{
			if(p.x<0 || p.y<0 || p.x>=width || p.y>=height) return;
			if(grid[p.y][p.x]=='#') return;
			if(grid[p.y][p.x]=='S' && next.collected<3 && next.altitude<10000) return;
			if(grid[p.y][p.x]!='S' && std::isalpha(grid[p.y][p.x]) && next.collected<(grid[p.y][p.x]-'A')) return;
			const auto forbidden = direction==0?1:direction==1?0:direction==2?3:2;
			const auto diff = grid[next.position.y][next.position.x]=='.'?-1:grid[next.position.y][next.position.x]=='+'?1:grid[next.position.y][next.position.x]=='-'?-2:-1;
			const auto collected = next.collected + (std::isalpha(grid[p.y][p.x]) && (next.collected==(grid[p.y][p.x]-'A')));

			if(max_height_with_from[direction][next.collected][p.y*width+p.x]<next.altitude+diff)
				max_height_with_from[direction][next.collected][p.y*width+p.x] = next.altitude+diff;
			else
				return;
			to_visit.push(waypoint{p, next.steps+1, next.altitude + diff, collected, forbidden});
		};


		if(next.forbidden!=0) try_add({next.position.x-1, next.position.y}, 0);
		if(next.forbidden!=1) try_add({next.position.x+1, next.position.y}, 1);
		if(next.forbidden!=2) try_add({next.position.x, next.position.y+1}, 2);
		if(next.forbidden!=3) try_add({next.position.x, next.position.y-1}, 3);
	}

	return 0;
}
