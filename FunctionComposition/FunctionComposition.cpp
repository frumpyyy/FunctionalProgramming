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

template <typename ... Args>
auto sum_all(Args... args) {
	return(args + ...);
}

template<typename T, typename F>
auto map_vec_transform(const std::vector<T>& inputVector, F func) -> std::vector<decltype(func(std::declval<T>()))> {
	using U = decltype(func(std::declval<T>()));
	std::vector<U> result;
	result.reserve(inputVector.size());
	std::transform(inputVector.begin(), inputVector.end(),
		std::back_inserter(result), [&func](const T& element) {
			return func(element);
		});

	return result;
}

//going to make a compose pipeline function to accumulate functions into one lambda capture
//compose needs to take in any given number of functions and return a function to be stored in a var
//once it works im going to pass into my map vector function to apply the pipeline to all variables within a given vec

template <typename F>
auto composePipeline(const F& func) {
	return func;
}

template <typename F1, typename F2>
auto composePipeline(const F1& func, const F2& func1) {
	return [func, func1](auto x) {
		return func(func1(x));
		};
}

template <typename F, typename... Functions>
auto composePipeline(const F& first, const Functions&... rest) {
	return composePipeline(first, composePipeline(rest...));
}

int main()
{
	const auto multiply10 = [](float in) -> float {return in * 10.0f; };
	const auto quater = [](float in) -> float {return in * 0.27f; };
	const auto roundToInt = [](float in) -> int {return std::round(in); };

	const auto pipeline = composePipeline(multiply10);
	const auto pipeline1 = composePipeline(quater, multiply10);
	const auto pipeline2 = composePipeline(roundToInt, quater, multiply10);

	std::cout << pipeline(2.0f) << '\n';
	std::cout << pipeline1(2.0f) << '\n';
	std::cout << pipeline2(2.0f) << '\n';

	//now applying through map vector function to apply to all in a vec
	const std::vector<float> dataset1 = { 1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,10.0f };
	const std::vector<float> dataset2 = { 5.0f, 11.0f, 15.5f, 20.5f, 1.9f };
	const auto test = map_vec_transform(dataset1, pipeline2);
	const auto test1 = map_vec_transform(dataset2, pipeline2);

	for (const auto v : test)
		std::cout << v << ", ";
	std::cout << '\n';


	for (const auto v : test1)
		std::cout << v << ", ";
	std::cout << '\n';

	//output is 5
	//std::cout << roundToInt(quater(multiply10(2.0f)));
}
