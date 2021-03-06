// a1.hpp
//
// Top-level executable

#pragma once

#include <iostream>

#include "b1.hpp"
#include "b2.hpp"
#include "b3.hpp"
#include "b4.hpp"
#include "b5.hpp"
#include "c1.hpp"
#include "c2.hpp"
#include "c3.hpp"
#include "d1.hpp"
#include "d2.hpp"
#include "e1.hpp"
#include "e2.hpp"
#include "e3.hpp"
#include "e4.hpp"

namespace examples {

// Class for this application
class a1 {
public:
	// Print from this application
	static void print();

private:
	// This library's name
	inline static const std::string mName { "a1" };

	// The date is modified by test scripts
	inline static const std::string mDate { "2020-02-28_215542" };
};

} // namespace examples

// Main program
int main();
