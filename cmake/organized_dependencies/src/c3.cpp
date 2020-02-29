// c3.cpp
//
// Simple library

#include "c3.hpp"

namespace examples {

// Only one public function
void c3::print(size_t indent) {
	std::cout << "[" << mDate << "] - "
		<< std::string(indent, ' ') << mName
		<< " - top\n";
	//d1::print(indent + 1);
	//d2::print(indent + 1);
	//e1::print(indent + 1);
	e2::print(indent + 1);
	e3::print(indent + 1);
	//e4::print(indent + 1);
	std::cout << "[" << mDate << "] - "
		<< std::string(indent, ' ') << mName
		<< " - end\n";
}

} // namespace examples
