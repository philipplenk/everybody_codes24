#include <iostream>
#include <iterator>
#include <string>
#include <unordered_set>
#include <vector>

#include <cctype>
#include <cstddef>

int main(int argc, char* argv[])
{
	const std::vector<std::string> original_grid{std::istream_iterator<std::string>{std::cin},{}};
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
	
	for(std::size_t row = 0; row<height; ++row)
		for(std::size_t column = 0; column<width; ++column)
			if(original_grid[row][column]=='.')
				std::cout<<grid[row][column];

	return 0;
}
