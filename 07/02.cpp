#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
	std::ifstream track_input("track");
	std::string track;
	track_input>>track;

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
	 	std::vector<char> steps;
	 	while(std::getline(strm, op, ','))
		 	steps.push_back(op.front());

		int step_idx = 0;
		for(int i=0; i<10;++i)
		{
			for(auto c: track)
			{
				if(c=='+')
					++current;
				else if(c=='-')
					--current;
				else
				{
					if(steps[step_idx]=='+')
						++current;
					else if(steps[step_idx]=='-')
						--current;
				}

				p.value+=current;
				step_idx = (step_idx+1)%steps.size();
			}
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
