#include <algorithm>
#include <iostream>
#include <iterator>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <cctype>
#include <cstddef>

/*
	Kind of an ugly abomination.
	I do beg your forgiveness ;_;
*/

void try_fill(std::vector<std::string>& grid)
{
	const auto width = grid[0].size();
	const auto height = grid.size();

	std::vector<std::unordered_set<char>> rows(height), columns(width);
	std::vector<int> rows_filled(height,0), columns_filled(width,0);
	for(std::size_t row = 0; row<height; ++row)
	{
		for(std::size_t column = 0; column<width; ++column)
		{
			if(!std::isalpha(grid[row][column])) continue;
			++rows_filled[row];
			++columns_filled[column];
			rows[row].insert(grid[row][column]);
			columns[column].insert(grid[row][column]);
		}
	}

	bool changed = true;
	while(changed)
	{
		changed = false;

		for(std::size_t row = 0; row<height; ++row)
		{
			for(std::size_t column = 0; column<width; ++column)
			{
				if(grid[row][column]!='.' && grid[row][column]!='?') continue;

				std::unordered_set<char> common;
				if(grid[row][column]=='.')
				{
					for(auto v: rows[row])
						if(columns[column].contains(v))
							common.insert(v);
				}

				std::optional<char> to_insert;
				if(common.size()==1)
				{
					to_insert = *common.begin();
				}
				else if(rows_filled[row]==7)
				{
					std::unordered_map<char, int> counts;
					for(std::size_t i=0; i<width; ++i)
						if(i!=column)
							++counts[grid[row][i]];

					for(const auto& [c, count]: counts)
						if(count==1)
							to_insert = c;
				}
				else if(columns_filled[column]==7)
				{
					std::unordered_map<char, int> counts;
					for(std::size_t i=0; i<height; ++i)
						if(i!=row)
							++counts[grid[i][column]];

					for(const auto& [c, count]: counts)
						if(count==1)
							to_insert = c;
				}

				if(to_insert)
				{
					changed = true;
					++rows_filled[row];
					++columns_filled[column];
					rows[row].insert(*to_insert);
					columns[column].insert(*to_insert);
					grid[row][column] = *to_insert;
				}
			}
		}
	}
}

int main(int argc, char* argv[])
{
	const std::vector<std::string> original_gridset{std::istream_iterator<std::string>{std::cin},{}};
	auto gridset = original_gridset;
	const auto width = gridset[0].size();
	const auto height = gridset.size();

	// First solve everything we can solve:
	bool changed = true;
	while(changed)
	{
		changed = false;
		for(std::size_t y = 0; y+8<=height; y+=6)
		{
			for(std::size_t x = 0; x+8<=width; x+=6)
			{
				std::vector<std::string> grid(8, std::string(8,'#'));
				for(std::size_t gy=0; gy<8; ++gy)
					for(std::size_t gx=0; gx<8; ++gx)
						grid[gy][gx] = gridset[y+gy][x+gx];

				try_fill(grid);
				for(std::size_t gy=0; gy<8; ++gy)
				{
					for(std::size_t gx=0; gx<8; ++gx)
					{
						if(!std::isalpha(gridset[y+gy][x+gx]) && std::isalpha(grid[gy][gx]))
						{
							changed = true;
							gridset[y+gy][x+gx] = grid[gy][gx];
						}
					}
				}
			}
		}
	}

	// Then do second pass over all blocks to determine and add the score of all complete ones:
	const auto is_complete = [&](int x, int y)
	{
		int dots = 0;
		for(std::size_t gy=0; gy<8; ++gy)
			for(std::size_t gx=0; gx<8; ++gx)
				dots+=gridset[y+gy][x+gx]=='.';

		return dots==0;;
	};

	const auto score_at = [&](int x, int y)
	{
		int n = 0, sum = 0;;
		for(std::size_t gy=0; gy<8; ++gy)
			for(std::size_t gx=0; gx<8; ++gx)
				if(original_gridset[y+gy][x+gx]=='.')
					sum+=++n*(gridset[y+gy][x+gx]-'A'+1);

		return sum;
	};
	
	int sum = 0;
	for(std::size_t y = 0; y+8<=height; y+=6)
	{
		for(std::size_t x = 0; x+8<=width; x+=6)
		{
			if(!is_complete(x,y)) continue;

			std::vector<std::unordered_map<char, int>> rows(height), columns(width);
			for(std::size_t gy=0; gy<8; ++gy)
			{
				for(std::size_t gx=0; gx<8; ++gx)
				{
					if(!std::isalpha(gridset[y+gy][x+gx])) continue;
					++rows[gy][gridset[y+gy][x+gx]];
					++columns[gx][gridset[y+gy][x+gx]];
				}
			}

			bool ok = true;
			for(const auto& row: rows)
				for(const auto& [_, count]: row)
					ok&=count<3;
			for(const auto& col: columns)
				for(const auto& [_, count]: col)
					ok&=count<3;

			if(ok)
				sum+=score_at(x, y);
		}
	}

	std::cout<<sum;	
	return 0;
}
