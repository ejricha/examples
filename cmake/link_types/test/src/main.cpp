// main.cpp

#include <iostream>

#include "a.h"
#include "b.h"

int main() {
	std::cout << "main() - top\n";

#ifdef PRINT_FROM_A
	A::print();
#endif // PRINT_FROM_A

#ifdef PRINT_FROM_B
	B::print();
#endif // PRINT_FROM_B

	std::cout << "main() - end\n";

	return EXIT_SUCCESS;
}
