#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <cstddef>

int main(int argc, char* argv[])
{
	std::string wheel_turns_str, skip;
	std::getline(std::cin, wheel_turns_str);
	std::getline(std::cin, skip);

	std::stringstream turns_strm{wheel_turns_str};
	std::vector<int> wheel_turns;
	char skip_c;
	for(int turn; turns_strm>>turn; turns_strm>>skip_c)
		wheel_turns.push_back(turn);

	std::vector<std::vector<int>> wheels;

	std::unordered_map<std::string, int> face_id;
	std::unordered_map<int, std::string> id_to_face;
	face_id["   "] = -1;
	id_to_face[-1] = "   ";
	int next_id = 0;
	for(std::string line; std::getline(std::cin, line); )
	{
		for(std::size_t i =0, wheel_idx = 0; i<line.size(); i+=4, wheel_idx+=1)
		{
			const auto face = line.substr(i,3);
			if(face=="   ") continue;
			if(!face_id.contains(face))
			{
				id_to_face[next_id] = face;
				face_id[face] = next_id++;
			}

			if(wheels.size()<=wheel_idx)
				wheels.resize(wheel_idx+1);

			wheels[wheel_idx].push_back(face_id[face]);
		}
	}

	struct score_set
	{
		unsigned long long min = std::numeric_limits<int>::max(), max = 0;
	};
	struct state_type
	{
		std::vector<int> s;
		int turns;
		bool operator<(const state_type& other) const
		{
			return std::tie(s,turns)<std::tie(other.s,other.turns);
		}
	};
	std::map<state_type, score_set> cache;
	const auto solve = [&](int turns, std::vector<int> state, auto rec)
	{
		auto key = state_type{state, turns};
		if(cache.contains(key)) return cache[key];
		for(std::size_t wheel=0; wheel<wheels.size(); ++wheel)
		{
			state[wheel]+=wheel_turns[wheel];
			state[wheel]%=wheels[wheel].size();
		}

		unsigned long long current_score = 0;
		std::unordered_map<char, int> counts;
		for(std::size_t wheel=0; wheel<wheels.size(); ++wheel)
		{
			++counts[id_to_face[wheels[wheel][state[wheel]]][0]];
			++counts[id_to_face[wheels[wheel][state[wheel]]][2]];
		}
		for(const auto& [_, count]: counts)
			current_score+=std::max(0,count-2);
		
		if(turns==0) return score_set{current_score, current_score};

		score_set followup{};
		for(int i=-1; i<=1; ++i)
		{
			auto next_state = state;
			for(std::size_t wheel=0;wheel<wheels.size(); ++wheel)
			{
				next_state[wheel]+=i;
				next_state[wheel]%=static_cast<int>(wheels[wheel].size());
				next_state[wheel]+=wheels[wheel].size();
				next_state[wheel]%=static_cast<int>(wheels[wheel].size());
			}
			const auto next_result = rec(turns-1, next_state, rec);
			followup.min = std::min(followup.min, next_result.min);
			followup.max = std::max(followup.max, next_result.max);
		}
		
		return cache[key] = score_set{current_score+followup.min, current_score+followup.max};
	};
	
	std::vector<int> initial_state(wheels.size(),0);

	score_set result{};
	for(int i=-1; i<=1; ++i)
	{
		auto state = initial_state;
		for(std::size_t wheel=0;wheel<wheels.size(); ++wheel)
		{
			state[wheel]+=i;
			state[wheel]%=static_cast<int>(wheels[wheel].size());
			state[wheel]+=wheels[wheel].size();
			state[wheel]%=static_cast<int>(wheels[wheel].size());
		}
		const auto current_result = solve(255, state, solve);
		result.min = std::min(result.min, current_result.min);
		result.max = std::max(result.max, current_result.max);
	}

	std::cout<<result.max<<' '<<result.min;
	return 0;
}
