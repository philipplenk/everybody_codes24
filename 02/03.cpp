#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

#include <cstddef>

struct trie
{
	void insert(std::string_view str)
	{
		auto* current = &root;
		for(auto c: str)
		{
			if(!current->children[c-'A'])
				current->children[c-'A'] = std::make_unique<node>();

			current = current->children[c-'A'].get();
		}
		current->value = str.size();
	}
	
	struct node
	{
		std::array<std::unique_ptr<node>, 26> children;
		std::size_t value = 0;
	};
	node root;
};

int main(int argc, char* argv[])
{
	std::string header;
	std::getline(std::cin, header);

	std::stringstream strm{header};
	std::string trash;
	std::getline(strm, trash, ':');

	trie t;
	for(std::string word; std::getline(strm, word, ',');)
		t.insert(word);

	std::vector<std::string> grid(std::istream_iterator<std::string>{std::cin}, {});
	const auto width = grid.front().size();
	const auto height = grid.size();
	std::vector<bool> used(width*height, false);

	for(std::size_t row = 0; row<height; ++row)
	{
		{
			std::unordered_set<trie::node*> current;
			current.insert(&t.root);
			for(std::size_t col = 0; col<2*width; ++col)
			{
				const auto c = grid[row][col%width];
				if(!std::isalpha(c))
				{
					current.clear();
					current.insert(&t.root);
					continue;
				}
				
				std::unordered_set<trie::node*> next;
				for(auto node: current)
				{
					if(auto child = node->children[c-'A'].get(); child)
					{
						next.insert(child);
						for(std::size_t j=0; j<child->value; ++j)
							used[row*width + (col - j)%width] = true;
					}
				}
				current = std::move(next);
				current.insert(&t.root);
			}
		}
		{
			std::unordered_set<trie::node*> current;
			current.insert(&t.root);
			for(std::size_t col = 0; col<2*width; ++col)
			{
				const auto x = (2*width-1-col)%width;
				const auto c = grid[row][x];
				if(!std::isalpha(c))
				{
					current.clear();
					current.insert(&t.root);
					continue;
				}
				
				std::unordered_set<trie::node*> next;
				for(auto node: current)
				{
					if(auto child = node->children[c-'A'].get(); child)
					{
						next.insert(child);
						for(std::size_t j=0; j<child->value; ++j)
						{
							const auto x = (2*width-1-(col-j))%width;
							used[row*width + x] = true;
						}
					}
				}
				current = std::move(next);
				current.insert(&t.root);
			}
		}
	}
	

	for(std::size_t col = 0; col<width; ++col)
	{
		{
			std::unordered_set<trie::node*> current;
			current.insert(&t.root);
			for(std::size_t row = 0; row<height; ++row)
			{
				const auto c = grid[row%height][col];
				if(!std::isalpha(c))
				{
					current.clear();
					current.insert(&t.root);
					continue;
				}
				
				std::unordered_set<trie::node*> next;
				for(auto node: current)
				{
					if(auto child = node->children[c-'A'].get(); child)
					{
						next.insert(child);
						for(std::size_t j=0; j<child->value; ++j)
							used[((row-j)%height)*width + col] = true;
					}
				}
				current = std::move(next);
				current.insert(&t.root);
			}
		}
		{
			std::unordered_set<trie::node*> current;
			current.insert(&t.root);
			for(std::size_t row = 0; row<height; ++row)
			{
				const auto y = (2*height -1 - row)%height;
				const auto c = grid[y][col];

				if(!std::isalpha(c))
				{
					current.clear();
					current.insert(&t.root);
					continue;
				}
				
				std::unordered_set<trie::node*> next;
				for(auto node: current)
				{
					if(auto child = node->children[c-'A'].get(); child)
					{
						next.insert(child);
						for(std::size_t j=0; j<child->value; ++j)
							used[((2*height-1 - (row-j))%height)*width + col] = true;
					}
				}
				current = std::move(next);
				current.insert(&t.root);
			}
		}
	}

	int count = std::ranges::count(used, true);
	std::cout<<count;
	return 0;
}
