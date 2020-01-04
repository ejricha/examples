// BaseClass.cpp
//
// Simple implementation of a base class

#include "BaseClass.hpp"

namespace cppmaryland {

// Constructor
BaseClass::BaseClass(std::string name):
	name_(name)
{
}

// Member functions
std::string BaseClass::GetName() const
{
	return name_;
}
std::string BaseClass::GetInfo() const
{
	return ("Base named [" + GetName() + "]");
}

// Overloaded output operator
std::ostream& operator<<(std::ostream& os, const BaseClass& o)
{
	return (os << o.GetInfo());
}

} // namespace cppmaryland
