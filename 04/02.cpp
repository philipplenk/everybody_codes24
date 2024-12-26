#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main(int argc, char* argv[])
{
	std::vector<int> numbers(std::istream_iterator<int>{std::cin},{});
	const auto min = *std::ranges::min_element(numbers);

	int sum = 0;
	for(const auto& v: numbers)
		sum+=v-min;

	std::cout<<sum;
	return 0;
}
