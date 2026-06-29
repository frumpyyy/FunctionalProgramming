#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

//const everywhere
//no raw loops
//std::transform, std::copy_if, std::sort

auto square_all(const std::vector<int>& inputVect) -> std::vector<int> {
	std::vector<int> result;
	result.reserve(inputVect.size());
	//std::transform applies a given function to every element and keeps every element, useful for element
	//modification but not element removing
	std::transform(inputVect.begin(), inputVect.end(),
		std::back_inserter(result),
		[](const int num) {return num * num; });
	return result;
}

auto keep_even(const std::vector<int>& inputVect) -> std::vector<int> {
	std::vector<int> result;
	result.reserve(inputVect.size());
	//std::copy_if only copies elements when the lambda returns true, useful for filtering vectors etc.
	std::copy_if(inputVect.begin(), inputVect.end(),
		std::back_inserter(result),
		[](const int num) {return num % 2 == 0; });
	return result;
}

auto sort_vector(const std::vector<int>& inputVect) -> std::vector<int> {
	std::vector<int> result = inputVect;
	std::sort(result.begin(), result.end(), [](const int a, const int b) {return a > b; });
	return result;
}

int main()
{
	const std::vector<int> ftest = { 0,1,2,3,4,5,6,7,8,9,10 };

	auto sqall = square_all(ftest);
	auto keepE = keep_even(sqall);
	auto sort = sort_vector(keepE);

	for (const auto v : sort)
		std::cout << v << ", ";
}


