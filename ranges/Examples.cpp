// Examples.cpp
//
// Run a lot of examples of ranges

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

#include "Lambdas.h"
#include "Overloads.h"
#include "Ranges.h"

namespace cppmaryland {

//using namespace Ranges;
using Type = int;

// Constant defining the number of elements to generate
static const size_t NumElementsToGenerate { 100'000'000 };

// Helper function to generate a vector of the given size
std::vector<Type> GenerateVector(size_t numElements)
{
	std::vector<Type> v(numElements);

	// Generator function does not use ranges (for now)
	iota(v.begin(), v.end(), 1);

	return v;
}

// Show a simple example of a view
void ShowView()
{
#ifdef RANGES_ENABLED
    for (auto e : Ranges::views::iota(1) | Ranges::views::take(9))
	{
		std::cout << e << ' ';
	}
#endif // RANGES_ENABLED
}

// Only show the even elements of a vector
void ShowEvenElements(const std::vector<Type>& v, const std::string& name)
{
#ifdef RANGES_ENABLED
	std::cout << "Ranges are enabled\n";
	/*
	const auto view = v | Ranges::views::filter(IsEven);
	//auto vEven = view | Ranges::to<std::vector<Type>>(); // Only works for range-v3
	//using namespace std::range;
	std::vector<Type> vEven;
	//Ranges::copy(view.begin(), view.end(), back_inserter(vEven));
	Ranges::copy(view, back_inserter(vEven));
	*/
	std::vector<Type> vEven;
	//Ranges::copy(Ranges::counted_iterator(v.begin(), 10), Ranges::default_sentinel, back_inserter(vEven));
#else
	std::vector<Type> vEven(v.size());
	std::cout << "Ranges are disabled\n";
	auto last = copy_if(v.cbegin(), v.cend(), vEven.begin(), IsEven);
	vEven.erase(last, vEven.cend());
#endif // RANGES_ENABLED
	PrintAbbrev(vEven, name);
}

// Show a delta of two times, or one time and the current time
template <typename ClockType>
void ShowDuration(const std::chrono::time_point<ClockType>& t1, const std::chrono::time_point<ClockType>& t2 = ClockType::now())
{
	using namespace std::chrono;

	auto duration = duration_cast<microseconds>(t2 - t1);
	std::cout << " (took " << std::fixed << std::setprecision(3) << duration.count() / 1'000'000.0 << " s)\n";
}

// Show a few ways of iterating a vector
void ExampleVector()
{
	const std::string name = "ShowEven";
	
	auto timer = std::chrono::high_resolution_clock::now();
	const auto v = GenerateVector(NumElementsToGenerate);
	PrintAbbrev(v, "Original");
	ShowDuration(timer);

	timer = std::chrono::high_resolution_clock::now();
	ShowEvenElements(v, name);
	ShowDuration(timer);

	timer = std::chrono::high_resolution_clock::now();
	ShowView();
	ShowDuration(timer);
}

} // namespace cppmaryland

// Run all the example functions
int main()
{
	using namespace cppmaryland;

	ExampleVector();
	return EXIT_SUCCESS;
}
