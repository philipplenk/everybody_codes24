#include <algorithm>
#include <array>
#include <iostream>
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

	int count = 0;
	for(std::string word; std::cin>>word; )
	{
		auto reversed = word;
		std::ranges::reverse(reversed);
		std::vector<bool> used(word.size(), false);
		for(bool rev = false; const auto& word: {word, reversed})
		{
			std::unordered_set<trie::node*> current;
			current.insert(&t.root);
			for(std::size_t i=0; i<word.size(); ++i)
			{
				const auto c = word[i];
				
				if(!std::isalpha(c)) continue;

				std::unordered_set<trie::node*> next;
				for(auto node: current)
				{
					if(auto child = node->children[c-'A'].get(); child)
					{
						next.insert(child);
						for(std::size_t j=0; j<child->value; ++j)
							used[rev?word.size()-1-(i-j):(i-j)] = true;
					}
				}
				current = std::move(next);
				current.insert(&t.root);
			}
			rev = true;
		}
		count+=std::ranges::count(used, true);
	}

	std::cout<<count;
	return 0;
}
