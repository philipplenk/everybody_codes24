#include <array>
#include <iostream>
#include <unordered_map>

int main(int argc, char* argv[])
{
	std::array options{30, 25, 24, 20, 16, 15, 10, 5, 3};
	std::unordered_map<int, int> cache;
	const auto solve = [&](int target, unsigned idx, auto rec)
	{
		if(target==0) return 0;
		if(idx>=options.size()) return target;
		if(target<options[idx]) return rec(target, idx+1, rec);
		
		const auto cache_key = target*options.size()+idx;
		if(cache.contains(cache_key))
			return cache[cache_key];

		const auto with = 1+rec(target - options[idx], idx, rec);
		const auto without = rec(target, idx+1, rec);
		return cache[cache_key] = std::min(with, without);
	};
	
	int sum = 0;
	for(int target; std::cin>>target;)
		sum+=solve(target, 0, solve);

	std::cout<<sum;
	return 0;
}
