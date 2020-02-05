// c.cpp
//
// Simple library

#include <iostream>

#include "c.hpp"

namespace cppmaryland {

void PrintC()
{
	std::cout << "   PrintC() - top\n";
	std::cout << "   PrintC() - calls EndInA()\n";
	EndInA();
	std::cout << "   PrintC() - end\n";
}

} // namespace cppmaryland
