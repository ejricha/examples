// Examples.cpp
//
// Run a lot of examples of ranges

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

#include "Lambdas.h"
#include "Overloads.h"
#include "Ranges.h"

namespace cppmaryland {

using namespace std;
using Type = int;

// Constant defining the number of elements to generate
static const size_t NumElementsToGenerate { 100'000'000 };

// Helper function to generate a vector of the given size
vector<Type> GenerateVector(size_t numElements)
{
	vector<Type> v(numElements);

	// Generator function does not use ranges (for now)
	iota(v.begin(), v.end(), 1);

	return v;
}

// Only show the even elements of a vector
void ShowEvenElements(const vector<Type>& v, const string& name)
{
#ifdef RANGES_ENABLED
	using namespace Ranges;
	std::cout << "Ranges are enabled\n";
	const auto vEven = v | views::filter(IsEven) | ranges::to_vector;
	PrintAbbrev(vEven, name);
#else
	vector<Type> vEven(v.size());
	std::cout << "Ranges are disabled\n";
	auto last = copy_if(v.cbegin(), v.cend(), vEven.begin(), IsEven);
	vEven.erase(last, vEven.cend());
	PrintAbbrev(vEven, name);
#endif // RANGES_ENABLED
}

// Show a delta of two times, or one time and the current time
template <typename ClockType>
void ShowDuration(const chrono::time_point<ClockType>& t1, const chrono::time_point<ClockType>& t2 = ClockType::now())
{
	using namespace chrono;

	auto duration = duration_cast<microseconds>(t2 - t1);
	cout << " (took " << fixed << setprecision(3) << duration.count() / 1'000'000.0 << " s)\n";
}

// Show a few ways of iterating a vector
void ExampleVector()
{
	const string name = "ShowEven";
	
	auto timer = chrono::high_resolution_clock::now();
	const auto v = GenerateVector(NumElementsToGenerate);
	PrintAbbrev(v, "Original");
	ShowDuration(timer);

	timer = chrono::high_resolution_clock::now();
	ShowEvenElements(v, name);
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
