// Overloads.hpp
//
// Overloaded operators for certain types

#include <iostream>
#include <string>
#include <vector>

namespace cppmaryland {

// Vector by element
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> v)
{
	os << "[";
	for (const auto e : v)
	{
		os << " " <<  e;
	}
	os << " ]";

	return os;
}

// Helper function to print an abbreviated vector
template <typename T>
void PrintAbbrev(const std::vector<T>& v, const std::string& s)
{
	// Always show the name
	std::cout << s << " : ";

	// Handle short vectors normally
	if (v.size() <= 10)
	{
		std::cout << v;
	}
	// Abbreviate long vectors
	else
	{
		std::cout << "[";
		for (size_t i = 0; i < 9; ++i)
		{
			std::cout << " " << v[i];
		}
		std::cout << " ... " << v[v.size() - 1] << " ]";
	}

	// Show the number of elements too
	std::cout << " (" << v.size() << ")\n";
}

} // namespace cppmaryland
