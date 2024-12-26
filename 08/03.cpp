#include <iostream>
#include <unordered_map>

int main(int argc, char* argv[])
{
	const auto blocks_for_width = [&](long long width, long long thickness)
	{
		return width*thickness;
	};
	
	constexpr auto mod = 10;
	constexpr auto to_add = 10;
	constexpr auto target = 202400000;
	
	long long factor;
	std::cin>>factor;

	std::unordered_map<long long, long long> blocks_in_column;
	blocks_in_column[0] = 1;
	
	const auto solve_boringly = [&](long long last, long long sum, long long width, auto rec) -> long long
	{
		const auto current = (factor*last)%mod + to_add;
		const auto current_blocks = blocks_for_width(width, current);
		for(int i=0; i<width; i+=2)
			blocks_in_column[i/2]+=current;

		long long free_blocks = 0;
		for(int i=0; i+2<width; i+=2)
			free_blocks+=(i==0?1:2)*((factor*width*blocks_in_column[i/2])%mod);

		if(sum + current_blocks - free_blocks >=target)
		{
			return sum + current_blocks - free_blocks;
		}

		return rec(current, sum + current_blocks, width+2, rec);
	};

	const auto required = solve_boringly(1, 1, 3, solve_boringly);
	std::cout<<required - target;
	
	return 0;
}

