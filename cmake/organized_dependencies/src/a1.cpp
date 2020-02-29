// a1.cpp
//
// Top-level executable

#include "a1.hpp"

namespace examples {

// Only one public function
void a1::print() {
	std::cout << "[" << mDate << "] - " << mName
		<< " - top\n";
	b1::print();
	b2::print();
	b3::print();
	b4::print();
	b5::print();
	c1::print();
	c2::print();
	c3::print();
	d1::print();
	d2::print();
	e1::print();
	e2::print();
	e3::print();
	e4::print();
	std::cout << "[" << mDate << "] - " << mName
		<< " - end\n";
}

} // namespace examples

// Main program
int main() {
	using namespace examples;

	// Call the static function
	a1::print();

	return EXIT_SUCCESS;
}
