// a2.cpp
//
// Top-level executable

#include "a2.hpp"

namespace examples {

// Only one public function
void a2::print() {
	std::cout << "[" << mDate << "] - " << mName
		<< "top\n";
	b1::print();
	//b2::print();
	b3::print();
	//b4::print();
	b5::print();
	//e7::print();
	std::cout << "[" << mDate << "] - " << mName
		<< "end\n";
}

} // namespace examples

// Main program
int main() {
	using namespace examples;

	// Call the static function
	a2::print();

	return EXIT_SUCCESS;
}
