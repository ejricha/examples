// b1.cpp
//
// Simple library

#include "b1.hpp"

namespace examples {

// Only one public function
void b1::print(size_t indent) {
	std::cout << mName << " [" << mDate << "] -"
		<< std::string(indent, ' ') << " top\n";
	e7::print(indent + 1);
	std::cout << mName << " [" << mDate << "] -"
		<< std::string(indent, ' ') << " end\n";
}

} // namespace examples
