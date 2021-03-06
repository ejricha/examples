// e1.hpp
//
// Simple library

#pragma once

#include <iostream>

namespace examples {

// Class for this library
class e1 {
public:
	// Print from this library
	static void print(size_t indent = 1);

private:
	// This library's name
	inline static const std::string mName { "e1" };

	// The date is modified by test scripts
	inline static const std::string mDate { "2020-02-28_215538" };
};

} // namespace examples
