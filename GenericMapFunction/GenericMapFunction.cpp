#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

//const everywhere
//no raw loops
//std::transform, std::copy_if, std::sort

//learning templated functions

//im assuming data type is T and then T add templates to float add if a float is supplied etc.

template <typename T>
T add(T a, T b) { return a + b; }

//this is really cool actually, manually declare function types wanted at call level, so want to conv float to int can do
template <typename T, typename U>
U convert(T con) { return static_cast<U>(con); }

//experimenting with the previous vector sort here, templating the vector type to see if can sort
template <typename T>
auto sort_vector(const std::vector<T>& inputVect) -> std::vector<T> {
	std::vector<T> result = inputVect;
	std::sort(result.begin(), result.end(), [](const T a, const T b) {return a > b; });
	return result;
}

int main()
{
	std::cout << add(0.1f, 1.0f) << '\n';
	std::cout << convert<float, int>(1.1f) << '\n';

	std::vector<int> testINT = { 0,1,2,3,4,5,6,7,8,9,10 };
	std::vector<char> testCHAR = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L' };

	const auto sorted = sort_vector(testINT);

	for (const auto v : sorted)
		std::cout << v << ", ";

	std::cout << '\n';

	const auto sortedChar = sort_vector(testCHAR);

	for (const auto v : sortedChar)
		std::cout << v << ", ";
}
