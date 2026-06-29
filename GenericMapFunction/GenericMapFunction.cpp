#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>

//const everywhere
//no raw loops
//std::transform, std::copy_if, std::sort

//learning templated functions

//im assuming data type is T and then T add templates to float add if a float is supplied etc.

template <typename T>
T add(T a, T b) { return a + b; }

//this is really cool actually, manually declare function types wanted at call level, so want to conv float to int can do
//manual type declaration
template <typename T, typename U>
U convert(T con) { return static_cast<U>(con); }

//experimenting with the previous vector sort here, templating the vector type to see if can sort - it works this is cool cool cool
template <typename T>
auto sort_vector(const std::vector<T>& inputVect) -> std::vector<T> {
	std::vector<T> result = inputVect;
	std::sort(result.begin(), result.end(), [](const T a, const T b) {return a > b; });
	return result;
}

//can let the compiler decide the type of a typename automatically

//manual version
template <typename T, typename U>
U applyingFuncManualType(const T& input, std::function<U(T)> func) {
	return func(input);
}

//compiler auto assign version, dont need to use declval since C++14 but am using here to gain a deeper understanding of what happends compiler side
//decltype(typename(std::declval)) means that when can set the output of a function to the type that the function func returns when inputted with typename T
//so in this case, with T = int and U = [](int x) {return x * 1.5f; }, we are stating that the return type for the template function should be a float, as U returns a float when supplied
//with an integer
template <typename T, typename U>
auto applyingFuncAutoType(const T& input, U func) -> decltype(func(std::declval<T>())) {
	return func(input);
}


int main()
{
	std::cout << add(0.1f, 1.0f) << '\n';
	std::cout << convert<float, int>(1.1f) << '\n';

	//this is very cool and useful
	std::vector<int> testINT = { 0,1,2,3,4,5,6,7,8,9,10 };
	std::vector<char> testCHAR = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L' };

	const auto sorted = sort_vector(testINT);

	for (const auto v : sorted)
		std::cout << v << ", ";

	std::cout << '\n';

	const auto sortedChar = sort_vector(testCHAR);

	for (const auto v : sortedChar)
		std::cout << v << ", ";

	std::cout << '\n';

	const auto res = applyingFuncManualType<int, float>(2, [](int x) -> float {
		return x * 1.5f;
		});

	std::cout << res << '\n';

	const auto resauto = applyingFuncAutoType(4, [](int x) {return x * 1.5f; });

	std::cout << resauto << '\n';




}
