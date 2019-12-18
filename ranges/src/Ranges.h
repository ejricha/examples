// Ranges.h
//
// Header file that includes the correct range library
//  based on preprocessor variables

#include <string>

// Default is that ranges are disabled
#undef RANGES_ENABLED

#if RANGES_V3
#define RANGES_ENABLED
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#include <range/v3/all.hpp>
#pragma GCC diagnostic pop
namespace cppmaryland {
	static const std::string Name = "V3";
	namespace Ranges = ranges;
} // namespace cppmaryland

#elif RANGES_NANO
#define RANGES_ENABLED
#include <nanorange.hpp>
namespace cppmaryland {
	static const std::string Name = "NANO";
	namespace Ranges = nano;
} // namespace cppmaryland

#elif RANGES_CMCSTL2
#define RANGES_ENABLED
#include <experimental/ranges/algorithm>
#include <experimental/ranges/range>
namespace cppmaryland {
	static const std::string Name = "CMCSTL2";
	namespace Ranges = std::experimental::ranges;
} // namespace cppmaryland

#else
//namespace Ranges = std;
namespace cppmaryland {
	static const std::string Name = "NONE";
} // namespace cppmaryland

#endif // RANGES_*
