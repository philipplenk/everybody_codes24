#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
	std::vector<std::string> grid;
	for(std::string line; std::getline(std::cin, line); grid.push_back(line));
	const int width = grid[0].size();
	const int height = grid.size();

	struct point2d
	{
		int x, y;
	};

	point2d start{}, end{};
	for(int y=0; y<height; ++y)
	{
		for(int x=0; x<width; ++x)
		{
			if(grid[y][x]=='S')
				start = {x,y};
			if(grid[y][x]=='E')
				end = {x,y};
		}
	}

	struct waypoint
	{
		point2d position;
		int level = 0;
		int distance = 0;

		bool operator<(const waypoint& other) const
		{
			return other.distance<distance;
		}
	};

	std::priority_queue<waypoint> to_visit;
	to_visit.push({start,0,0});

	std::vector<bool> visited(width*height, false);
	while(!to_visit.empty())
	{
		const auto next = to_visit.top();
		to_visit.pop();

		if(next.position.x==end.x && next.position.y==end.y)
		{
			std::cout<<next.distance;
			break;
		}

		if(visited[next.position.y*width+next.position.x])
			continue;
		visited[next.position.y*width+next.position.x] = true;


		const auto try_push = [&](point2d pos)
		{
			if(pos.x<0 || pos.x>=width || pos.y<0 || pos.y>=height) return;
			if(visited[pos.y*width+pos.x]) return;
			if(!std::isdigit(grid[pos.y][pos.x]) && grid[pos.y][pos.x]!='E') return;

			const auto level_target = grid[pos.y][pos.x]=='E'?0:grid[pos.y][pos.x]-'0';
			const auto cost = std::min({std::abs(next.level-level_target), 1+next.level+(9-level_target), 1+level_target+(9-next.level)});
			to_visit.push({pos, level_target, next.distance+1+cost});
		};

		try_push({next.position.x-1,next.position.y});
		try_push({next.position.x+1,next.position.y});
		try_push({next.position.x,next.position.y+1});
		try_push({next.position.x,next.position.y-1});
	}

	return 0;
}
