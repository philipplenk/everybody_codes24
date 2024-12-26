#include <algorithm>
#include <iostream>
#include <limits>
#include <set>
#include <sstream>
#include <string>
#include <vector>

struct point3d
{
	int x, y, z;
	friend auto operator<=>(const point3d&, const point3d&) = default;
};

int main(int argc, char* argv[])
{
	std::set<point3d> seen;
	std::set<point3d> leaves;
	for(std::string line; std::getline(std::cin, line); )
	{
		std::stringstream linestrm{line};
		int x = 0, y = 0, z = 0;
		for(std::string instruction; std::getline(linestrm, instruction, ',');)
		{
			std::stringstream strm{instruction};
			char c;
			int step;
			strm>>c>>step;

			switch(c)
			{
				case 'U': for(int i=0; i<step; ++i) { y+=1; seen.insert({x,y,z}); }  break;
				case 'D': for(int i=0; i<step; ++i) { y-=1; seen.insert({x,y,z}); }  break;
				case 'L': for(int i=0; i<step; ++i) { x+=1; seen.insert({x,y,z}); }  break;
				case 'R': for(int i=0; i<step; ++i) { x-=1; seen.insert({x,y,z}); }  break;
				case 'F': for(int i=0; i<step; ++i) { z+=1; seen.insert({x,y,z}); }  break;
				case 'B': for(int i=0; i<step; ++i) { z-=1; seen.insert({x,y,z}); }  break;
			}
		}
		leaves.insert({x,y,z});
	}

	int min_y = std::numeric_limits<int>::max(), max_y = std::numeric_limits<int>::min();
	for(const auto& p: leaves)
	{
		min_y = std::min(min_y, p.y);
		max_y = std::max(max_y, p.y);
	}

	const auto distance_to = [&](point3d from, point3d to)
	{
		std::set<point3d> visited;
		
		std::vector<point3d> current;
		current.push_back(from);

		for(int i=0;; ++i)
		{
			std::vector<point3d> next;
			const auto try_add = [&](point3d target)
			{
				if(visited.contains(target)) return;
				if(!seen.contains(target)) return;
				visited.insert(target);
				next.push_back(target);
			};
			for(auto p: current)
			{
				if(p==to) return i;
				try_add({p.x+1, p.y, p.z});
				try_add({p.x-1, p.y, p.z});
				try_add({p.x, p.y+1, p.z});
				try_add({p.x, p.y-1, p.z});
				try_add({p.x, p.y, p.z+1});
				try_add({p.x, p.y, p.z-1});
			}
			current = std::move(next);
		}
	};

	int min = std::numeric_limits<int>::max();
	for(int y=min_y; y<=max_y; ++y)
	{
		if(!seen.contains({0,y,0})) continue;
		int sum = 0;
		for(const auto& l: leaves)
			sum+=distance_to(l, {0, y, 0});

		min = std::min(min, sum);
	}
	
	std::cout<<min;
	return 0;
}
