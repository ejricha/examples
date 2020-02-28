// e1.cpp
//
// Simple library

#include "e1.hpp"

namespace examples {

// Only one public function
void e1::print(size_t indent) {
	std::cout << "[" << mDate << "] - "
		<< std::string(indent, ' ') << mName
		<< "\n";
}

} // namespace examples
