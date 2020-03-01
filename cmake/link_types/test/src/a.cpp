// a.cpp

#include "a.h"

#include <iostream>

#include "b.h"

void A::print() {
#ifdef PRINT_FROM_B
	std::cout << "  A - top\n  ";
	B::print();
	std::cout << "  A - end\n";
#else
	std::cout << "  A\n";
#endif // PRINT_FROM_B
}
