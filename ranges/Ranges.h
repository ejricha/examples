// Ranges.h
//
// Header file that includes the correct range library
//  based on preprocessor variables

// Default is that ranges are disabled
#undef RANGES_ENABLED

#if RANGES_V3
#define RANGES_ENABLED
#include <range/v3/algorithm.hpp>
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
#include <experimental/ranges/algorithm>
#include <experimental/ranges/concepts>
#include <experimental/ranges/functional>
#include <experimental/ranges/iterator>
#include <experimental/ranges/memory>
#include <experimental/ranges/random>
#include <experimental/ranges/range>
#include <experimental/ranges/type_traits>
#include <experimental/ranges/utility>
namespace cppmaryland {
	namespace Ranges = std::experimental::ranges;
} // namespace cppmaryland

#else
//namespace Ranges = std;
namespace cppmaryland {
} // namespace cppmaryland

#endif // RANGES_*
