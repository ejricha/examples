// a.cpp
//
// Simple library

#include <iostream>

#include "a.hpp"

namespace cppmaryland {

void PrintA()
{
	std::cout << " PrintA() - top\n";
	std::cout << " PrintA() - calls PrintB()\n";
	PrintB();
	std::cout << " PrintA() - end\n";
}

void EndInA()
{
	std::cout << " EndInA() called\n";
}

} // namespace cppmaryland
