// e3.cpp
//
// Simple library

#include "e3.hpp"

namespace examples {

// Only one public function
void e3::print(size_t indent) {
	std::cout << "[" << mDate << "] - "
		<< std::string(indent, ' ') << mName
		<< "\n";
}

} // namespace examples
