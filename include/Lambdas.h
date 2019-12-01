// Lambdas.h
//
// Useful lambdas operators

namespace cppmaryland {

// Return true if a number is even
auto IsEven = [](auto n) { return ((n % 2) == 0); };
auto IsDivisibleByFive = [](auto n) { return ((n % 5) == 0); };
auto IsDivisibleBySeven = [](auto n) { return ((n % 7) == 0); };
auto IsDivisibleBySeventy = [](auto n) { return ((n % 70) == 0); };
auto LessThanTwenty = [](auto n) { return (n < 20); };

// Square a number
auto Square = [](auto n) { return (n * n); };

} // namespace cppmaryland
