// e7.hpp
//
// Simple library

#pragma once

#include <iostream>

namespace examples {

// Class for this library
class e7 {
public:
	// Print from this library
	static void print(size_t indent = 0);

private:
	// This library's name
	inline static const std::string mName { "e7" };

	// The date is modified by test scripts
	inline static const std::string mDate { "2020-02-28_115000" };
};

} // namespace examples
