// c1.hpp
//
// Simple library

#pragma once

#include <iostream>

#include "d1.hpp"
#include "d2.hpp"
#include "e1.hpp"
#include "e2.hpp"
#include "e3.hpp"
#include "e4.hpp"

namespace examples {

// Class for this library
class c1 {
public:
	// Print from this library
	static void print(size_t indent = 1);

private:
	// This library's name
	inline static const std::string mName { "c1" };

	// The date is modified by test scripts
	inline static const std::string mDate { "2020-02-28_215527" };
};

} // namespace examples
