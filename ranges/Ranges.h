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

#elif RANGES_V3
#define RANGES_ENABLED
//#include <range/v3/algorithm.hpp>
#include <range/v3/all.hpp>
namespace cppmaryland {
	namespace Ranges = ranges;
} // namespace cppmaryland

#elif RANGES_NANO
#define RANGES_ENABLED
#include <nanorange.hpp>
namespace cppmaryland {
	namespace Ranges = nano;
} // namespace cppmaryland

#elif RANGES_CMCSTL2
#define RANGES_ENABLED
#include <experimental/ranges/range>
#include <experimental/ranges/algorithm>
#include <experimental/ranges/iterator>
namespace cppmaryland {
	namespace Ranges = std::experimental::ranges;
} // namespace cppmaryland

#else
//namespace Ranges = std;
namespace cppmaryland {
} // namespace cppmaryland

#endif // RANGES_*
