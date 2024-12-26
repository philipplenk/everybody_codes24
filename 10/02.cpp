#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

#include <cctype>
#include <cstddef>

int power(const std::vector<std::string>& original_grid)
{
	auto grid = original_grid;
	const auto width = grid[0].size();
	const auto height = grid.size();

	std::vector<std::unordered_set<char>> rows(height), columns(width);
	for(std::size_t row = 0; row<height; ++row)
	{
		for(std::size_t column = 0; column<width; ++column)
		{
			if(!std::isalpha(grid[row][column])) continue;
			rows[row].insert(grid[row][column]);
			columns[column].insert(grid[row][column]);
		}
	}

	bool done = false;
	while(!done)
	{
		done = true;

		for(std::size_t row = 0; row<height; ++row)
		{
			for(std::size_t column = 0; column<width; ++column)
			{
				if(grid[row][column]!='.') continue;
				done = false;
				std::unordered_set<char> common;
				for(auto v: rows[row])
					if(columns[column].contains(v))
						common.insert(v);

				if(common.size()==1)
				{
					rows[row].insert(*common.begin());
					columns[column].insert(*common.begin());
					grid[row][column] = *common.begin();
				}
			}
		}
	}

	int result = 0, n = 0;
	for(std::size_t row = 0; row<height; ++row)
		for(std::size_t column = 0; column<width; ++column)
			if(original_grid[row][column]=='.')
				result+=++n*(grid[row][column]-'A'+1);

	return result;
}

int main(int argc, char* argv[])
{
	std::vector<std::vector<std::string>> grids;

	int sum = 0;
	for(std::string line; std::getline(std::cin, line);)
	{
		if(line.empty())
		{
			for(const auto& grid: grids)
				sum+=power(grid);

			grids.clear();
			continue;
		}
		
		std::stringstream strm{line};
		std::string part;
		for(std::size_t idx = 0; strm>>part; ++idx)
		{
			if(grids.size()<=idx)
				grids.resize(idx+1);
			grids[idx].push_back(part);
		}
	}

	for(const auto& grid: grids)
		sum+=power(grid);

	std::cout<<sum;
	return 0;
}
