#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

int main(int argc, char* argv[])
{
	std::ifstream track_input("track2");
	std::vector<std::string> track_map;
	for(std::string line; std::getline(track_input, line);)
		track_map.push_back(line);

	const int track_height = track_map.size();
	const int track_width = track_map.front().size(); 

	std::cout<<track_width<<'x'<<track_height<<'\n';

	std::string track;
	int x = 1, y = 0;
	int last_x = 0, last_y = 0;
	while(track_map[y][x]!='S')
	{
		track.push_back(track_map[y][x]);
		if(x-1!=last_x && x>0 && track_map[y][x-1]!=' ')
		{
			last_x = x;
			last_y = y;
			x = x-1;
		}
		else if(x+1!=last_x && x+1<track_width && track_map[y][x+1]!=' ')
		{
			last_x = x;
			last_y = y;
			x = x+1;
		}
		else if(y-1!=last_y && y>0 && track_map[y-1][x]!=' ')
		{
			last_x = x;
			last_y = y;
			y = y-1;
		}
		else if(y+1!=last_y && y+1<track_height && track_map[y+1][x]!=' ')
		{
			last_x = x;
			last_y = y;
			y = y+1;
		}
		else
		{
			std::cout<<track_width<<' '<<track_height<<'\n';
			std::cout<<x<<' '<<y<<';'<<last_x<<' '<<last_y<<'\n';
			break;
		}

	}
	track+='=';
	std::cout<<track<<'\n';

	const auto run_track = [&](const auto& steps)
	{
		long long current = 10, result = 0;
		int step_idx = 0;
		for(int i=0; i<2024;++i)
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

				result+=current;
				step_idx = (step_idx+1)%steps.size();
			}
		}
		return result;
	};

	struct plan
	{
		long long value = 0;
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

	 	std::vector<char> steps;
	 	while(std::getline(strm, op, ','))
	 	{
		 	steps.push_back(op.front());
	 	}

		p.value = run_track(steps);
	 	
	 	plans.push_back(p);
	}

	for(const auto& p: plans)
		std::cout<<p.identifier<<' '<<p.value<<'\n';

	const auto target = plans.front().value;

	std::unordered_map<std::string, long> cache;
	const auto count_rec = [&](std::string prefix, auto rec) -> long
	{
		if(prefix.size()==11)
			return run_track(prefix)>target?1l:0l;

		if(cache.contains(prefix))
			return cache[prefix];

		int plus = 0, minus = 0, equal = 0;
		for(auto c: prefix)
		{
			plus+=c=='+';
			minus+=c=='-';
			equal+=c=='=';
		}

		long result = 0;
		if(minus<3) result+=rec(prefix+'-', rec);
		if(plus<5) result+=rec(prefix+'+', rec);
		if(equal<3) result+=rec(prefix+'=', rec);

		return cache[prefix]=result;
	};

	std::cout<<count_rec("", count_rec);
	return 0;
}
