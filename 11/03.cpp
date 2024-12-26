#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

int main(int argc, char* argv[])
{
	struct termite
	{
		std::vector<std::string> transforming_into;
	};

	std::unordered_map<std::string, termite> termites;
	for(std::string line; std::getline(std::cin,line);)
	{
		std::stringstream strm{line};
		char id0, id1, id2;
		strm>>id0>>id1>>id2;
		std::vector<std::string> target;
		for(char skip, value0, value1, value2; strm>>skip>>value0>>value1>>value2;)
			target.push_back(((std::string{}+value0)+value1)+value2);

		termites[((std::string{}+id0)+id1)+id2] = {target};
	}

	const auto count_starting_with = [&](std::string start)
	{
		std::unordered_map<std::string, long> counts;
		counts[start] = 1;
		for(int day = 0; day<20; ++day)
		{
			std::unordered_map<std::string, long> next_counts;
			for(auto [t, count]: counts)
			{
				for(auto target: termites[t].transforming_into)
					next_counts[target]+=count;
			}
			counts = std::move(next_counts);
		}

		long sum = 0;
		for(const auto& [_,c]: counts)
			sum+=c;

		return sum;
	};

	long low = std::numeric_limits<long>::max(), high = std::numeric_limits<long>::min();

	for(const auto& [type, _]: termites)
	{
		const auto result = count_starting_with(type);
		low = std::min(low, result);
		high = std::max(high, result);
	}
	
	std::cout<<high-low;
	return 0;
}
