// e7.cpp
//
// Simple library

#include "e7.hpp"

namespace examples {

// Only one public function
void e7::print(size_t indent) {
	std::cout << "[" << mDate << "] - "
		<< std::string(indent, ' ') << mName
		<< "\n";
}

} // namespace examples
