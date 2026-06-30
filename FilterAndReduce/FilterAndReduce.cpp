#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <functional>
#include <string>

//const everywhere
//no raw loops
//std::transform, std::copy_if, std::sort

auto keepLen4(const std::vector<std::string>& inputVector) -> std::vector<std::string> {
	std::vector<std::string> result;
	result.reserve(inputVector.size());
	std::copy_if(inputVector.begin(), inputVector.end(),
		std::back_inserter(result), [](const std::string& in) {
			return in.length() >= (size_t)4;
		});
	return result;
}

auto stringToUpper(const std::string& in) -> std::string {
	std::string result;
	result.reserve(in.size());
	std::transform(in.begin(), in.end(), std::back_inserter(result), [](unsigned char c) {
		return static_cast<char>(std::toupper(c));
		});
	return result;
}

auto convertToUpper(const std::vector<std::string>& inputVector) -> std::vector<std::string> {
	std::vector<std::string> result;
	result.reserve(inputVector.size());
	std::transform(inputVector.begin(), inputVector.end(),
		std::back_inserter(result), stringToUpper);

	return result;
}

auto convertVectorToString(const std::vector<std::string>& inputVector) -> std::string {
	return std::accumulate(inputVector.begin(), inputVector.end(),
		std::string{},
		[](std::string acc, const std::string& in) {
			if (!acc.empty())
				acc += ',';
			acc += in;
			return acc;
		});
}

int main()
{
	const std::vector<std::string> test = { "be", "see", "bear", "we", "wear", "wheat" };

	const auto keep = keepLen4(test);
	const auto upper = convertToUpper(keep);
	const auto concat = convertVectorToString(upper);


	for (const auto v : keep)
		std::cout << v << ", ";
	std::cout << '\n';

	for (const auto v : upper)
		std::cout << v << ", ";
	std::cout << '\n';

	std::cout << concat << '\n';

}
