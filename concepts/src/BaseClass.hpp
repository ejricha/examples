// BaseClass.hpp
//
// Simple interface for a base class

#pragma once

#include <iostream>
#include <string>

namespace cppmaryland {

class BaseClass
{
public:
	// Constructor and destructor
	BaseClass(std::string name);
	virtual ~BaseClass() = default;

	// Member functions
	std::string GetName() const;
	virtual std::string GetInfo() const;

private:
	// Only a single member variable
	std::string name_;
};

// Overloaded output operator
std::ostream& operator<<(std::ostream& os, const BaseClass& o);

} // namespace cppmaryland
