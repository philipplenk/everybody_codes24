#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

int main(int argc, char* argv[])
{
	std::vector<long long> numbers(std::istream_iterator<int>{std::cin},{});
	const long long target = std::accumulate(numbers.begin(), numbers.end(), 0ll)/numbers.size();

	long long sum = 0;
	for(const auto& v: numbers)
		sum+=std::abs(v-target);

	std::cout<<sum;
	return 0;
}
