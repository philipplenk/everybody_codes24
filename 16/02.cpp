#include <algorithm>
#include <iostream>
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

	struct state_info
	{
		unsigned long long seen_at = 0;
		unsigned long long score = 0;
	};
	
	std::unordered_map<std::string, state_info> seen;
	std::vector<int> state(wheels.size(),0);
	
	unsigned long long score = 0;
	const auto bound = 202420242024;
	for(unsigned long long i=0;i<bound; ++i)
	{
		for(std::size_t wheel=0; wheel<wheels.size(); ++wheel)
		{
			state[wheel]+=wheel_turns[wheel];
			state[wheel]%=wheels[wheel].size();
		}

		std::unordered_map<char, int> counts;
		std::string combined;
		for(std::size_t wheel=0; wheel<wheels.size(); ++wheel)
		{
			combined+=id_to_face[wheels[wheel][state[wheel]]];
			++counts[id_to_face[wheels[wheel][state[wheel]]][0]];
			++counts[id_to_face[wheels[wheel][state[wheel]]][2]];
		}
		for(const auto& [_, count]: counts)
			score+=std::max(0,count-2);

		if(seen.contains(combined))
		{
			const auto remaining = bound - i;
			const auto loop_length = i - seen[combined].seen_at;
			const auto loop_count = remaining/loop_length;
			const auto loop_value = score - seen[combined].score;

			score+=loop_value*loop_count;
			i+=loop_count*loop_length;

			continue;
		}

		seen[combined].seen_at = i;
		seen[combined].score = score;
	}

	std::cout<<score;
	return 0;
}
