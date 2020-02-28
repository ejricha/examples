// a3.cpp
//
// Top-level executable

#include "a3.hpp"

namespace examples {

// Only one public function
void a3::print() {
	std::cout << "[" << mDate << "] - " << mName
		<< "top\n";
	//b1::print();
	e7::print();
	std::cout << "[" << mDate << "] - " << mName
		<< "end\n";
}

} // namespace examples

// Main program
int main() {
	using namespace examples;

	// Call the static function
	a3::print();

	return EXIT_SUCCESS;
}
