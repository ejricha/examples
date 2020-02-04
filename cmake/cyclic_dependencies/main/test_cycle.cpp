// test_cycle.cpp
//
// Simple app that uses libraries cyclically

#include <iostream>

#include "test_cycle.hpp"

int main()
{
	std::cout << "main() - top\n";
	std::cout << "main() - calling PrintA()\n";
	cppmaryland::PrintA();
	std::cout << "main() - calling PrintB()\n";
	cppmaryland::PrintB();
	std::cout << "main() - calling PrintC()\n";
	cppmaryland::PrintC();
	std::cout << "main() - end\n";

	return EXIT_SUCCESS;
}
