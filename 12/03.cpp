#include <algorithm>
#include <iostream>
#include <vector>

#include <cstddef>

int main(int argc, char* argv[])
{
	struct point2d
	{
		int x, y;
	};

	std::vector<point2d> sources{{0,0}, {0,-1}, {0,-2}}, targets;
	for(point2d p; std::cin>>p.x>>p.y;)
		targets.push_back(p);

	std::ranges::sort(targets,[](const auto& lhs, const auto& rhs)
	{
		return std::min(lhs.x,lhs.y)<std::min(rhs.x,rhs.y);
	});

	for(auto& p: targets)
		p.y = -p.y;

	int result = 0;
	for(auto target: targets)
	{
		for(int y = target.y, time = 0; y<=0; ++y, ++time)
		{
			int best = -1, cost = 1000000;
			for(std::size_t i=0; i<sources.size(); ++i)
			{
				const auto dist_y = y - sources[i].y;
				const auto dist_x = (target.x-time) - sources[i].x;
				if(dist_x>time) continue;

				int required_power = 999999999;
				if(2*(dist_x - dist_y)/3<dist_x && (dist_x-dist_y)>0 && (dist_x - dist_y)%3==0)
					required_power = (dist_x - dist_y)/3;

				if(dist_y<0 && -2*dist_y>dist_x && -dist_y<=dist_x)
					required_power = std::min(required_power, -dist_y);

				if(required_power*static_cast<int>(i+1)<cost)
				{
					cost = required_power*(i+1);
					best = i;
				}
			}
			if(best>=0)
			{
				std::cerr<<"Hitting target "<<target.x<<'x'<<target.y<<" with "<<best<<" at cost "<<cost<<'\n';
				std::cerr<<"Time was "<<time<<'\n';
				result+=cost;
				break;
			}
		}
	}

	std::cout<<result;
	return 0;
}
