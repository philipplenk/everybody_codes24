#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

int main(int argc, char* argv[])
{
	struct termite
	{
		std::vector<char> transforming_into;
	};

	std::unordered_map<char, termite> termites;
	for(std::string line; std::getline(std::cin,line);)
	{
		std::stringstream strm{line};
		char id;
		strm>>id;
		std::vector<char> target;
		for(char skip, value; strm>>skip>>value;)
			target.push_back(value);

		termites[id] = {target};
	}

	std::unordered_map<char, int> counts;
	counts['Z'] = 1;
	for(int day = 0; day<10; ++day)
	{
		std::unordered_map<char, int> next_counts;
		for(auto [t, count]: counts)
		{
			for(auto target: termites[t].transforming_into)
				next_counts[target]+=count;
		}
		counts = std::move(next_counts);
	}

	int sum = 0;
	for(const auto& [_,c]: counts)
		sum+=c;

	std::cout<<sum;
	return 0;
}
