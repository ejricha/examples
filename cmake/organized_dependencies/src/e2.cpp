// e2.cpp
//
// Simple library

#include "e2.hpp"

namespace examples {

// Only one public function
void e2::print(size_t indent) {
	std::cout << "[" << mDate << "] - "
		<< std::string(indent, ' ') << mName
		<< "\n";
}

} // namespace examples
