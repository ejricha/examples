// Examples.cpp
//
// Run a lot of examples of ranges

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <functional>
#include <iterator>
#include <numeric>
#include <vector>

#include "Lambdas.h"
#include "Overloads.h"
#include "Ranges.h"

namespace cppmaryland {

// We can easily change the vector element type
using Number = int;

// A function pointer
using FunctionPointer = std::function<void(const std::vector<Number>&, const std::string&)>;

// Helper function to generate a vector of the given size
std::vector<Number> GenerateVector(size_t numElements)
{
	std::vector<Number> v(numElements);

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
void ShowElementsEven(const std::vector<Number>& v, const std::string& name)
{
	std::vector<Number> vResult;
	vResult.reserve(v.size());
#ifdef RANGES_ENABLED
	auto theView = v | Ranges::views::filter(IsEven);
	Ranges::for_each(theView, [&vResult](const Number n) { vResult.push_back(n); });
#else
	// Reserve potentially more elements than we need
	vResult.reserve(v.size());
	auto last = copy_if(v.cbegin(), v.cend(), vResult.begin(), IsEven);
	vResult.erase(last, vResult.cend());
#endif // RANGES_ENABLED
	PrintAbbrev(vResult, name);
}

// Only show the elements of a vector divisible by 2, 5, and 7
void ShowElementsDivisibleBy70(const std::vector<Number>& v, const std::string& name)
{
#ifdef RANGES_ENABLED
	std::vector<Number> vResult;
	vResult.reserve(v.size());
	auto theView = v | Ranges::views::filter(IsEven)
		| Ranges::views::filter(IsDivisibleByFive)
		| Ranges::views::filter(IsDivisibleBySeven);
	Ranges::for_each(theView, [&vResult](const Number n) { vResult.push_back(n); });
#else
	// Reserve potentially more elements than we need
	std::vector<Number> vStep1(v.size());
	auto last = copy_if(v.cbegin(), v.cend(), vStep1.begin(), IsEven);
	vStep1.erase(last, vStep1.cend());
	std::vector<Number> vStep2(vStep1.size());
	last = copy_if(vStep1.begin(), last, vStep2.begin(), IsDivisibleByFive);
	vStep2.erase(last, vStep2.cend());
	std::vector<Number> vResult(vStep2.size());
	last = copy_if(vStep2.begin(), last, vResult.begin(), IsDivisibleBySeven);
	vResult.erase(last, vResult.cend());
#endif // RANGES_ENABLED
	PrintAbbrev(vResult, name);
}

// Only show the elements of a vector divisible by 2, 5, and 7
void ShowElementsEvenSquared(const std::vector<Number>& v, const std::string& name)
{
	std::vector<Number> vResult;
#ifdef RANGES_ENABLED
# ifdef RANGES_CMCSTL2
	std::cout << "Ranges::views::transform does not work for CMCSTL2\n";
# else
	auto theView = v | Ranges::views::filter(IsEven) | Ranges::views::transform(Square);
	Ranges::for_each(theView, [&vResult](const Number n) { vResult.push_back(n); });
# endif // RANGES_CMCSTL2
#else
	// Reserve potentially more elements than we need
	std::vector<Number> vEven(v.size());
	auto last = copy_if(v.cbegin(), v.cend(), vEven.begin(), IsEven);
	vEven.erase(last, vEven.cend());
	vResult.reserve(v.size());
#endif // RANGES_ENABLED
	PrintAbbrev(vResult, name);
}

// Show a delta of two times, or one time and the current time
// Also return the time in seconds
template <typename ClockType>
double ShowDuration(const std::chrono::time_point<ClockType>& t1, const std::chrono::time_point<ClockType>& t2 = ClockType::now())
{
	using namespace std::chrono;

	const auto durationSeconds = duration_cast<microseconds>(t2 - t1).count() / 1'000'000.;
	std::cout << " (took " << std::fixed << std::setprecision(6) << durationSeconds << " s)\n";
	return durationSeconds;
}

// Run the specified fuction in a loop up to a billion times
void LoopTests(const std::string& operation, FunctionPointer fn)
{
	auto timer = std::chrono::high_resolution_clock::now();

	// Open the output file
	std::ofstream fout("results_" + Name + "_" + operation + ".dat");
	fout << "# N\t" << operation << "\n";

	auto v = GenerateVector(0);
	
	// Loop increasing the number of elements
	for (size_t numElements = 100; numElements < 1'000'000'000; numElements *= 3)
	{
		fout << numElements << "\t";

		timer = std::chrono::high_resolution_clock::now();
		v = GenerateVector(numElements);
		PrintAbbrev(v, "Original");
		ShowDuration(timer);

		timer = std::chrono::high_resolution_clock::now();
		fn(v, operation);
		fout << ShowDuration(timer) << "\n";
	}
}

// Run the tests for the following functions
void RunTests()
{
	LoopTests("Even", ShowElementsEven);
	LoopTests("EvenThenSquared", ShowElementsEvenSquared);
	LoopTests("DivisibleBy70", ShowElementsDivisibleBy70);
}

} // namespace cppmaryland

// Run all the example functions
int main()
{
	using namespace cppmaryland;

	RunTests();
	return EXIT_SUCCESS;
}
