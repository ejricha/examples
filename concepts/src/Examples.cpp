// Examples.cpp
//
// Run a lot of examples of concepts

#include <iostream>
#include <string>

// Include the concepts library from range-v3 library,
//  and prevent a conversion warning/error
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#include <range/v3/all.hpp>
#pragma GCC diagnostic pop

namespace cppmaryland {

// Static string for testing
const static std::string GlobalString { "CppMaryland" };

// Templated function without concepts
template <typename UnconfirmedInt>
char AtIndex(const UnconfirmedInt i)
{
	return GlobalString[i];
}

// Run all the simple tests
void SimpleTests()
{
	std::cout << "Testing on string " << GlobalString << " with size " << GlobalString.size() << "\n";
	for (size_t i = 0; i < GlobalString.size(); ++i)
	{
		std::cout << " [" << i << "] = " << AtIndex(i) << "\n";
	}
	std::cout << "\n";

	// This compiles fine
	size_t i = 3;
	std::cout << "AtIndex(" << i << ") = " << AtIndex(i) << "\n";
	
	// This will not compile
	// TODO: prevent override
	float f = 2.2;
	std::cout << "AtIndex(" << f << ") = " << AtIndex(f) << "\n";
}

// Run the tests for the following functions
void RunTests()
{
	// Run all the simple tests first
	SimpleTests();

	std::cout << std::endl;
}

} // namespace cppmaryland

// Run all the example functions
int main()
{
	using namespace cppmaryland;

	RunTests();
	return EXIT_SUCCESS;
}
