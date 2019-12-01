// Examples.cpp
//
// Run a lot of examples of ranges

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <iterator>
#include <numeric>
#include <vector>

#include "Lambdas.h"
#include "Overloads.h"
#include "Ranges.h"

namespace cppmaryland {

//using namespace Ranges;
using Number = int;

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
void ShowEvenElements(const std::vector<Number>& v, const std::string& name)
{
	// Reserve potentially more elements than we need
	std::vector<Number> vEven;
	vEven.reserve(v.size());
#ifdef RANGES_ENABLED
	std::cout << "Ranges are enabled\n";
	auto view = v | Ranges::views::filter(IsEven);
	Ranges::for_each(view, [&vEven](const Number n) { vEven.push_back(n); });
#else
	std::cout << "Ranges are disabled\n";
	auto last = copy_if(v.cbegin(), v.cend(), vEven.begin(), IsEven);
	vEven.erase(last, vEven.cend());
#endif // RANGES_ENABLED
	PrintAbbrev(vEven, name);
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

// Show a few ways of iterating a vector
void ExampleVector()
{
	const std::string name = "ShowEven";
	auto timer = std::chrono::high_resolution_clock::now();

	// Open the output file
	std::ofstream fout("results_" + Name + ".dat");
	fout << "#\tN\tOrig\tShowEven\n";
	
	// Loop increasing the number of elements
	for (size_t numElements = 100; numElements < 1'000'000'000; numElements *= 3)
	{
		fout << numElements << "\t";

		timer = std::chrono::high_resolution_clock::now();
		const auto v = GenerateVector(numElements);
		PrintAbbrev(v, "Original");
		fout << ShowDuration(timer) << "\t";

		timer = std::chrono::high_resolution_clock::now();
		ShowEvenElements(v, name);
		ShowDuration(timer);
		fout << ShowDuration(timer) << "\n";

		std::cout << std::endl;
	}
}

} // namespace cppmaryland

// Run all the example functions
int main()
{
	using namespace cppmaryland;

	ExampleVector();
	return EXIT_SUCCESS;
}
