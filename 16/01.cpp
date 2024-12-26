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

	std::vector<int> state(wheels.size(),0);
	for(int i=0;i<100; ++i)
	{
		for(std::size_t wheel=0; wheel<wheels.size(); ++wheel)
		{
			state[wheel]+=wheel_turns[wheel];
			state[wheel]%=wheels[wheel].size();
		}
	}

	for(std::size_t wheel=0; wheel<wheels.size(); ++wheel)
		std::cout<<id_to_face[wheels[wheel][state[wheel]]];
	
	return 0;
}
