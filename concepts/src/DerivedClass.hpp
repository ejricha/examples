// DerivedClass.hpp
//
// Simple interface for a base class

#pragma once

#include <iostream>
#include <string>

#include "BaseClass.hpp"

namespace cppmaryland {

class DerivedClass : public BaseClass
{
public:
	// Constructor and destructor
	DerivedClass(std::string name, int number);
	virtual ~DerivedClass() = default;

	// Member functions
	int GetNumber() const;
	std::string GetInfo() const override;

private:
	// One additional class member
	int number_;
};

// Overloaded output operator
std::ostream& operator<<(std::ostream& os, const DerivedClass& o);

} // namespace cppmaryland
