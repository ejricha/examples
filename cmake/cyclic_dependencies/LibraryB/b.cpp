// b.cpp
//
// Simple library

#include <iostream>

#include "b.hpp"

namespace cppmaryland {

void PrintB()
{
	std::cout << "  PrintB() - top\n";
	std::cout << "  PrintB() - calls PrintC()\n";
	PrintC();
	std::cout << "  PrintB() - end\n";
}

} // namespace cppmaryland
