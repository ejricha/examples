// d2.hpp
//
// Simple library

#pragma once

#include <iostream>

#include "e1.hpp"
#include "e2.hpp"
#include "e3.hpp"
//#include "e4.hpp"

namespace examples {

// Class for this library
class d2 {
public:
	// Print from this library
	static void print(size_t indent = 1);

private:
	// This library's name
	inline static const std::string mName { "d2" };

	// The date is modified by test scripts
	inline static const std::string mDate { "2020-02-28_215538" };
};

} // namespace examples
