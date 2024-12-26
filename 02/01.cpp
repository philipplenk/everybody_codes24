#include <array>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_set>

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
		current->terminal = true;
	}
	
	struct node
	{
		std::array<std::unique_ptr<node>, 26> children;
		bool terminal = false;
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
		std::unordered_set<trie::node*> current;
		current.insert(&t.root);

		for(auto c: word)
		{
			if(!std::isalpha(c)) continue;

			std::unordered_set<trie::node*> next;
			for(auto node: current)
			{
				if(auto child = node->children[c-'A'].get(); child)
				{
					next.insert(child);
					count+=child->terminal;
				}
			}
			current = std::move(next);
			current.insert(&t.root);
		}
	}

	std::cout<<count;
	return 0;
}
