#include <catch2/catch_test_macros.hpp>

#include <rvarago/std_optional_extras/all.hpp>

#include <optional>

namespace optx = rvarago::std_optional_extras;

template <typename T> constexpr std::optional<T> none;

TEST_CASE("Filter-in when engaged with a value satisfying a predicate",
          "[filter]") {
  constexpr auto is_even = [](int const x) -> bool { return (x % 2) == 0; };

  STATIC_REQUIRE(optx::filter(none<int>, is_even) == none<int>);
  STATIC_REQUIRE(optx::filter(std::optional{1}, is_even) == none<int>);
  STATIC_REQUIRE(optx::filter(std::optional{42}, is_even) == std::optional{42});
}
