#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

int main(int argc, char* argv[])
{
	std::vector<std::vector<int>> columns;
	for(std::string line; std::getline(std::cin, line);)
	{
		std::stringstream strm{line};
		for(int idx = 0, value; strm>>value; ++idx)
		{
			if(static_cast<int>(columns.size())<=idx)
				columns.resize(idx+1);

			columns[idx].push_back(value);
		}
	}

	const auto dance = [&](int column_idx)
	{
		const auto value = columns[column_idx].front();
		columns[column_idx].erase(columns[column_idx].begin());

		const auto target_column = (column_idx+1)%columns.size();
		const auto target_size = columns[target_column].size();
		const auto target_pos = (value-1)%(target_size*2);
		const auto target_idx = target_pos<target_size?target_pos:(2*target_size-target_pos);

		columns[target_column].insert(columns[target_column].begin()+target_idx, value);
	};

	std::unordered_set<std::string> seen;
	long long max = 0;
	for(int i=0; ; ++i)
	{
		dance(i%columns.size());

		long long number = 0;
		std::string key;
		for(const auto& column: columns)
		{
			number = number*10000 + column.front();
			for(const auto& v: column)
				key+=std::to_string(v);
			key+='_';
		}

		max = std::max(number, max);

		if(seen.contains(key)) break;
		seen.insert(key);
	}

	std::cout<<max;
	return 0;
}

