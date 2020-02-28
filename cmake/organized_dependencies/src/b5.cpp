// b5.cpp
//
// Simple library

#include "b5.hpp"

namespace examples {

// Only one public function
void b5::print(size_t indent) {
	std::cout << "[" << mDate << "] - "
		<< std::string(indent, ' ') << mName
		<< "top\n";
	c1::print(indent + 1);
	//c2::print(indent + 1);
	c3::print(indent + 1);
	//d1::print(indent + 1);
	//d2::print(indent + 1);
	e1::print(indent + 1);
	//e2::print(indent + 1);
	e3::print(indent + 1);
	e4::print(indent + 1);
	std::cout << "[" << mDate << "] - "
		<< std::string(indent, ' ') << mName
		<< "end\n";
}

} // namespace examples
