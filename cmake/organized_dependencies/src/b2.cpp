// b2.cpp
//
// Simple library

#include "b2.hpp"

namespace examples {

// Only one public function
void b2::print(size_t indent) {
	std::cout << "[" << mDate << "] - "
		<< std::string(indent, ' ') << mName
		<< "top\n";
	e7::print(indent + 1);
	std::cout << "[" << mDate << "] - "
		<< std::string(indent, ' ') << mName
		<< "end\n";
}

} // namespace examples
