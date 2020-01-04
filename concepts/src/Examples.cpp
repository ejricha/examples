// Examples.cpp
//
// Run a lot of examples of concepts

#include <iostream>
#include <string>

// Include the concepts from the CMCSTL2 library
//#include <stl2/concepts.hpp>

// Simple Base and Derived classes
#include "BaseClass.hpp"
#include "DerivedClass.hpp"

namespace cppmaryland {

// Ignore conversion errors for a while
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-conversion"

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

	// double is cast to an int
	TestConcrete(102.222);

	// string produces a compile error:
	// error: invalid conversion from ‘const char*’ to ‘int’ [-fpermissive]
	//TestConcrete("one hundred three");

	// BaseClass, by reference and pointer
	BaseClass base("base");
	TestConcrete(base);
	TestConcrete(&base);

	// DerivedClass, by reference and pointer
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

	// BaseClass, by reference and pointer
	BaseClass base("base");
	TestTemplate(base);
	TestTemplate(&base);

	// DerivedClass, by reference and pointer
	DerivedClass derived("derived", 204);
	TestTemplate(derived);
	TestTemplate(&derived);

	std::cout << std::endl;
}

// Tests of functions with concepts
void FunctionsConcepts()
{
	std::cout << "FunctionsConcepts:\n";
	/*
	TestConcepts(7);
	DerivedClass derived("derived", 7);
	TestConcepts(derived);
	TestConcepts(&derived);
	*/
	std::cout << std::endl;
}

// ===========================================================


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
	/*
	float f = 2.2f;
	std::cout << "AtIndex(" << f << ") = " << AtIndex(f) << "\n";
	*/
}

/*
CPP_template(class Iter, class Sent, class Comp = ...some_default...)
	(requires sentinel_for<Sent, Iter>)
void my_algorithm(Iter first, Sent last, Comp comp = Comp{})
{
	// ...
}
*/

// Run the tests for the following functions
void RunTests()
{
	// Show examples of function with various levels of parameters
	FunctionsConcrete();
	FunctionsTemplate();
	FunctionsConcepts();

	// Run all the simple tests next
	SimpleTests();

	std::cout << std::endl;
}

#pragma GCC diagnostic pop
} // namespace cppmaryland

// Run all the example functions
int main()
{
	using namespace cppmaryland;

	RunTests();
	return EXIT_SUCCESS;
}
