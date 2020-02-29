// c1.cpp
//
// Simple library

#include "c1.hpp"

namespace examples {

// Only one public function
void c1::print(size_t indent) {
	std::cout << "[" << mDate << "] - "
		<< std::string(indent, ' ') << mName
		<< " - top\n";
	d1::print(indent + 1);
	d2::print(indent + 1);
	e1::print(indent + 1);
	e2::print(indent + 1);
	e3::print(indent + 1);
	e4::print(indent + 1);
	std::cout << "[" << mDate << "] - "
		<< std::string(indent, ' ') << mName
		<< " - end\n";
}

} // namespace examples
