#include <iostream>
#include <sstream>
#include <string>
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

	for(int i=0; i<10; ++i)
		dance(i%columns.size());

	for(const auto& v: columns)
		std::cout<<v.front();

	return 0;
}

