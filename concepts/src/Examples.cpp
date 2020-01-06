// Examples.cpp
//
// Run a lot of examples of concepts

#include <iostream>
#include <list>
#include <set>
#include <string>
#include <type_traits>
#include <vector>

#include <cassert>

// Include the concepts from the CMCSTL2 library
#include <stl2/concepts.hpp>

#include "BaseClass.hpp"
#include "DerivedClass.hpp"
#include "Overloads.hpp"

namespace cppmaryland {

// Namespace alias for concepts
namespace Concepts = std::experimental::ranges::v1;

// Define a concept to see if a type is a pointer
template <typename T>
	concept IsPointer =
	std::is_pointer_v<T>;

// Static string for testing
const static std::string GlobalString { "CppMaryland" };

// ===========================================================
// Show examples of function with various levels of parameters
// ===========================================================

// Tests of concrete functions
void TestConcrete(int i)
{
	std::cout << "  TestConcrete(int = " << i << ")\n";
}
void TestConcrete(BaseClass base) // narrowing
{
	std::cout << "  TestConcrete(BaseClass = " << base << ")\n";
}
void TestConcrete(const BaseClass* base)
{
	std::cout << "  TestConcrete(const BaseClass* = " << *base << ")\n";
}
void FunctionsConcrete()
{
	std::cout << "FunctionsConcrete:\n";

	// int
	TestConcrete(101);

	// double produces a compile error:
	// error: conversion from ‘double’ to ‘int’ changes value from ‘1.0222199999999999e+2’ to ‘102’ [-Werror=float-conversion]
	//TestConcrete(102.222);

	// string produces a compile error:
	// error: invalid conversion from ‘const char*’ to ‘int’ [-fpermissive]
	//TestConcrete("one hundred three");

	// BaseClass, by value and pointer
	BaseClass base("base");
	TestConcrete(base);
	TestConcrete(&base);

	// DerivedClass, by value and pointer
	DerivedClass derived("derived", 104);
	TestConcrete(derived);
	TestConcrete(&derived);

	std::cout << std::endl;
}

// Tests of templated functions
template <typename T>
void TestTemplate(T t)
{
	std::cout << "  TestTemplate(T = " << t << ")\n";
}
template <typename T>
void TestTemplate(const T* p)
{
	std::cout << "  TestTemplate(const T* = " << p << ")\n";
}
template <>
void TestTemplate<int>(int i)
{
	std::cout << "  TestTemplate(int = " << i << ")\n";
}
template <>
void TestTemplate<BaseClass*>(BaseClass* base)
{
	std::cout << "  TestTemplate(BaseClass* = " << *base << ")\n";
}
void FunctionsTemplate()
{
	std::cout << "FunctionsTemplate:\n";

	// int
	TestTemplate(201);

	// double, uses the default template
	TestTemplate(202.222);

	// string, uses the default template
	TestTemplate("two hundred three");

	// BaseClass, by value and pointer
	BaseClass base("base");
	TestTemplate(base);
	TestTemplate(&base);

	// DerivedClass, by value and pointer
	DerivedClass derived("derived", 204);
	TestTemplate(derived);
	TestTemplate(&derived);

	std::cout << std::endl;
}

// Tests of functions with concepts
template <typename T>
void TestConcepts(T t)
{
	std::cout << "  TestConcepts([UNCONSTRAINED] = " << t << ")\n";
}
template <typename T>
	requires Concepts::integral<T>
void TestConcepts(T t)
{
	std::cout << "  TestConcepts([integral] = " << t << ")\n";
}
template <typename T>
	requires Concepts::floating_point<T>
void TestConcepts(T t)
{
	std::cout << "  TestConcepts([floating_point] = " << t << ")\n";
}
template <typename T>
	requires IsPointer<T>
void TestConcepts(T t)
{
	std::cout << "  TestConcepts([IsPointer] = " << *t << ")\n";
}
void FunctionsConcepts()
{
	std::cout << "FunctionsConcepts:\n";

	// int
	TestConcepts(301);

	// double
	TestConcepts(302.222);

	// string
	TestConcepts("three hundred three");

	// BaseClass, by value and pointer
	BaseClass base("base");
	TestConcepts(base);
	TestConcepts(&base);

	// DerivedClass, by value and pointer
	DerivedClass derived("derived", 304);
	TestConcepts(derived);
	TestConcepts(&derived);

	std::cout << std::endl;
}

// ===========================================================

// Templated function without concepts
template <typename UnconfirmedInt>
char AtIndex(const UnconfirmedInt i)
{
	return GlobalString[i];
}

// Long form of concepts
template <typename T>
	requires Concepts::integral<T>
char AtIndexConstrained(const T i)
{
	return GlobalString[i];
}

// Short form of concepts
template <Concepts::integral T>
char AtIndexConstrainedShort(const T i)
{
	return GlobalString[i];
}

// Even shorter form of concepts
char AtIndexConstrainedShorter(const Concepts::integral i)
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

	// Try both an integer and a floating point number as the index
	const size_t i = 3;
	const float f = 2.2f;

	// Unconstrained templates

	// This compiles fine
	std::cout << "AtIndex(" << i << ") = " << AtIndex(i) << "\n";

	// This will not compile:
	//std::cout << "AtIndex(" << f << ") = " << AtIndex(f) << "\n";
	// error: conversion from ‘float’ to ‘std::__cxx11::basic_string<char>::size_type’ {aka ‘long unsigned int’} may change value [-Werror=float-conversion]

	// Use concepts to constrain templates
	
	// Normal form
	std::cout << "AtIndexConstrained(" << i << ") = " << AtIndexConstrained(i) << "\n";
	//std::cout << "AtIndexConstrained(" << f << ") = " << AtIndexConstrained(f) << "\n";
	// error: cannot call function ‘char cppmaryland::AtIndexConstrained(T) [with T = float]’
	
	// Short form
	std::cout << "AtIndexConstrainedShort(" << i << ") = " << AtIndexConstrainedShort(i) << "\n";
	//std::cout << "AtIndexConstrainedShort(" << f << ") = " << AtIndexConstrainedShort(f) << "\n";
	// error: cannot call function ‘char cppmaryland::AtIndexConstrainedShort(T) [with T = float]’
	
	// Shorter form
	std::cout << "AtIndexConstrainedShorter(" << i << ") = " << AtIndexConstrainedShorter(i) << "\n";
	//std::cout << "AtIndexConstrainedShorter(" << f << ") = " << AtIndexConstrainedShorter(f) << "\n";
	// error: cannot call function ‘char cppmaryland::AtIndexConstrainedShorter(auto:1) [with auto:1 = float]’
	
	// Prevent warning/error about unused variable
	(void)f;
	std::cout << std::endl;
}

// Show a really long error message
template <typename Container>
size_t IndexOfLargest(const Container& c)
{
	// If the container is empty, return 0
	if (c.empty())
	{
		return 0;
	}

	// Store the first value as the largest thus far
	using V = typename Container::value_type;
	auto it = c.cbegin();
	std::pair<size_t, V> largest(0, *it);

	// Iterate through the rest of the values
	++it;
	for (size_t index = 0; it != c.cend(); ++it)
	{
		if (*it > largest.second)
		{
			largest.first = index;
			largest.second = *it;
		}
		++index;
	}
	
	// Retur the index of the largest value
	return largest.first;
}

// Test with a few valid containers, and an invalid one
void TestIndexOfLargest()
{
	size_t i;

	std::vector<int> a1 { 1, 2, 5, 7, 3, 5, 4, 6 };
	i = IndexOfLargest(a1);
	std::cout << a1 << " max is " << a1[i] << " @ index " << i << "\n";
	assert((i == 3) && (a1[i] == 7));

	std::vector<int> a2 { 1, 2, 5, 4, 5 };
	i = IndexOfLargest(a2);
	std::cout << a2 << " max is " << a2[i] << " @ index " << i << "\n";
	assert((i == 2) && (a2[i] == 5));

	std::vector<int> a3 { 6, 1 };
	i = IndexOfLargest(a3);
	std::cout << a3 << " max is " << a3[i] << " @ index " << i << "\n";
	assert((i == 6) && (a3[i] == 0));

	std::vector<int> a4 { -1 };
	i = IndexOfLargest(a4);
	std::cout << a4 << " max is " << a4[i] << " @ index " << i << "\n";
	assert((i == 0) && (a4[i] == -1));

	std::vector<int> a5 { };
	i = IndexOfLargest(a5);
	std::cout << a5 << " max is @ index " << i << "\n";
	assert(i == 0);

	// Try a few different containers
	std::list<int> l1 { 1, 2, 5, 4, 5 };
	IndexOfLargest(l1);
	std::multiset<int> m1 { 1, 2, 5, 4, 5 };
	IndexOfLargest(m1);

	std::cout << std::endl;
}

// Run the tests for the following functions
void RunTests()
{
	// Show examples of function with various levels of parameters
	FunctionsConcrete();
	FunctionsTemplate();
	FunctionsConcepts();

	// Run all the simple tests next
	SimpleTests();
	
	// Find the index of the largest value
	TestIndexOfLargest();
}

} // namespace cppmaryland

// Run all the example functions
int main()
{
	using namespace cppmaryland;

	RunTests();
	return EXIT_SUCCESS;
}
