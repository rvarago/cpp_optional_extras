#include <catch2/catch_test_macros.hpp>

#include <optional>

#include <rvarago/optional_extras/all.hpp>

namespace optx = rvarago::optional_extras;

template <typename T> constexpr std::optional<T> none;

TEST_CASE("When engaged with a value satisfying a predicate", "[filter]") {
  constexpr auto is_even = [](int const x) -> bool { return (x % 2) == 0; };

  STATIC_REQUIRE(optx::filter(none<int>, is_even) == none<int>);
  STATIC_REQUIRE(optx::filter(std::optional{1}, is_even) == none<int>);
  STATIC_REQUIRE(optx::filter(std::optional{42}, is_even) == std::optional{42});
}

TEST_CASE("When engaged with a value equal to the argument", "[contains]") {
  STATIC_REQUIRE(optx::contains(none<int>, 42) == false);
  STATIC_REQUIRE(optx::contains(std::optional{1}, 42) == false);
  STATIC_REQUIRE(optx::contains(std::optional{42}, 42) == true);
}
