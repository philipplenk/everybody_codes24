#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <cstddef>

int main(int argc, char* argv[])
{
	struct node
	{
		std::unordered_set<std::string> connections;
	};

	std::unordered_map<std::string, node> nodes;
	for(std::string line;std::getline(std::cin, line);)
	{
		std::stringstream strm{line};
		std::string name;
		std::getline(strm, name, ':');

		for(std::string target; std::getline(strm, target, ','); )
			nodes[name].connections.insert(target);
	}

	std::vector<std::string> current;
	current.push_back("__RR");
	nodes["__RR"] = nodes["RR"];

	for(;;)
	{
		int leaves = 0;
		for(const auto& c: current)
			leaves+=c.back()=='@';

		if(leaves==1)
		{
			for(const auto& c: current)
				if(c.back()=='@')
				{
					std::cout<<'R';
					for(std::size_t i=4;i<c.size();i+=4)
						std::cout<<c[i];

					return 0;
				}
		}
		std::vector<std::string> next;
		for(const auto& c: current)
		{
			auto target = c.substr(c.size()-4);
			for(auto child: nodes[target].connections)
				next.push_back(c+child);
		}
		current = std::move(next);
	}
	
	return 0;
}
