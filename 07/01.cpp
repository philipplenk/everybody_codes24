#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
	struct plan
	{
		int value = 0;
		char identifier;
	};
	std::vector<plan> plans;

	for(std::string line;std::getline(std::cin,line);)
	{
		std::stringstream strm{line};
	 	plan p;
	 	strm>>p.identifier;
	 	char skip;
	 	strm>>skip;
	 	std::string op;

	 	int current = 10;
	 	while(std::getline(strm, op, ','))
	 	{
		 	if(op=="+") ++current;
		 	if(op=="-") --current;
		 	p.value+=current;
	 	}
	 	plans.push_back(p);
	 	std::cout<<p.identifier<<' '<<p.value<<'\n';
	}

	std::ranges::sort(plans,[](const auto& lhs, const auto& rhs)
	{
		return lhs.value>rhs.value;
	});

	for(const auto& p: plans)
		std::cout<<p.identifier;

	return 0;
}
