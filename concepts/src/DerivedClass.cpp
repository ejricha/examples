// DerivedClass.cpp
//
// Simple implementation of a base class

#include "DerivedClass.hpp"

namespace cppmaryland {

// Constructor
DerivedClass::DerivedClass(std::string name, int number):
	BaseClass(name), number_(number)
{
}

// Member functions
int DerivedClass::GetNumber() const
{
	return number_;
}
std::string DerivedClass::GetInfo() const
{
	return ("Derived named [" + GetName() + "] and number " + std::to_string(GetNumber()));
}

// Overloaded output operator
std::ostream& operator<<(std::ostream& os, const DerivedClass& o)
{
	return (os << o.GetInfo());
}

} // namespace cppmaryland
