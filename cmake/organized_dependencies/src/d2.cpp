// d2.cpp
//
// Simple library

#include "d2.hpp"

namespace examples {

// Only one public function
void d2::print(size_t indent) {
	std::cout << "[" << mDate << "] - "
		<< std::string(indent, ' ') << mName
		<< " - top\n";
	e1::print(indent + 1);
	e2::print(indent + 1);
	e3::print(indent + 1);
	//e4::print(indent + 1);
	std::cout << "[" << mDate << "] - "
		<< std::string(indent, ' ') << mName
		<< " - end\n";
}

} // namespace examples
