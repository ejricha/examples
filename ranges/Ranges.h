// Ranges.h
//
// Header file that includes the correct range library
//  based on preprocessor variables

// Default is that ranges are disabled
#undef RANGES_ENABLED

#ifdef RANGES_EXPERIMENTAL
#define RANGES_ENABLED
#include <experimental/ranges/algorithm>
namespace cppmaryland {
	namespace Ranges = std::experimental::ranges;
} // namespace cppmaryland

#elif RANGES_NIEBLER
#define RANGES_ENABLED
//#include <range/v3/algorithm.hpp>
#include <range/v3/all.hpp>
namespace cppmaryland {
	namespace Ranges = ranges;
} // namespace cppmaryland

#else
//namespace Ranges = std;
namespace cppmaryland {
} // namespace cppmaryland

#endif // RANGES_*
