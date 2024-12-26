#include <iostream>

int main(int argc, char* argv[])
{
	const auto blocks_for_width = [&](long long width, long long thickness)
	{
		return width*thickness;
	};
	
	constexpr auto mod = 1111;
	constexpr auto target = 20240000;
	
	long long factor;
	std::cin>>factor;
	
	long long final_width = 0;
	const auto solve_boringly = [&](long long last, long long target, long long width, auto rec) -> long long
	{
		const auto current = (factor*last)%mod;
		const auto current_blocks = blocks_for_width(width, current) ;

		if(current_blocks>=target)
		{
			final_width = width;
			return current_blocks;
		}

		return current_blocks + rec(current, target-current_blocks, width+2, rec);
	};

	const auto required = solve_boringly(1, target-1, 3, solve_boringly)+1;
	std::cout<<(required-target)*final_width;
	
	return 0;
}
