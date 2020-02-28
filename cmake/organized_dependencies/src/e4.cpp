// e4.cpp
//
// Simple library

#include "e4.hpp"

namespace examples {

// Only one public function
void e4::print(size_t indent) {
	std::cout << "[" << mDate << "] - "
		<< std::string(indent, ' ') << mName
		<< "\n";
}

} // namespace examples
