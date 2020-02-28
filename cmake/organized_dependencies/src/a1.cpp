// a1.cpp
//
// Top-level executable

#include "a1.hpp"

namespace examples {

// Only one public function
void a1::print() {
	std::cout << mName << " [" << mDate << "] - top\n";
	b1::print();
	e7::print();
	std::cout << mName << " [" << mDate << "] - end\n";
}

} // namespace examples

// Main program
int main() {
	using namespace examples;

	// Call the static function
	a1::print;

	return EXIT_SUCCESS;
}
