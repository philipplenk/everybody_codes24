#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

#include <cstddef>

int main(int argc, char* argv[])
{
	std::vector<std::string> grid(std::istream_iterator<std::string>{std::cin},{});
	const auto width = grid.front().size();
	const auto height = grid.size();

	std::vector<int> depth(width*height, 0);
	for(std::size_t y=0; y<height; ++y)
		for(std::size_t x=0; x<width; ++x)
			depth[y*width+x] = grid[y][x]=='#';

	const auto step = [&]()
	{
		bool changed = false;
		
		auto next = depth;
		for(std::size_t y=0; y<height; ++y)
		{
			for(std::size_t x=0; x<width; ++x)
			{
				bool ok = depth[y*width+x]>0;
				ok&=x==0 || (depth[y*width+(x-1)]==depth[y*width+x]);
				ok&=x==width-1 || (depth[y*width+(x+1)]==depth[y*width+x]);
				ok&=y==0 || (depth[(y-1)*width+x]==depth[y*width+x]);
				ok&=y==height-1 || (depth[(y+1)*width+x]==depth[y*width+x]);

				if(ok) ++next[y*width+x];
				changed|=ok;
			}
		}

		depth = std::move(next);
		return changed;
	};

	while(step());
		
	std::cout<<std::accumulate(depth.begin(), depth.end(), 0);
	return 0;
}
