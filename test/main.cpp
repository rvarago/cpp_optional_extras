#include <catch2/catch_test_macros.hpp>

#include <optional>
#include <utility>

#include <rvarago/optional_extras/all.hpp>

namespace optx = rvarago::optional_extras;

template <typename T> constexpr std::optional<T> none;

TEST_CASE("When engaged with a value satisfying a predicate", "[filter]") {
  static constexpr auto is_even = [](int const x) -> bool {
    return (x % 2) == 0;
  };

  STATIC_REQUIRE(optx::filter(none<int>, is_even) == none<int>);
  STATIC_REQUIRE(optx::filter(std::optional{1}, is_even) == none<int>);
  STATIC_REQUIRE(optx::filter(std::optional{42}, is_even) == std::optional{42});
}

TEST_CASE("When engaged with a value equal to the argument", "[contains]") {
  STATIC_REQUIRE(optx::contains(none<int>, 42) == false);
  STATIC_REQUIRE(optx::contains(std::optional{1}, 42) == false);
  STATIC_REQUIRE(optx::contains(std::optional{42}, 42) == true);
}

TEST_CASE("When both are engaged then merge them", "[zip_with]") {
  static constexpr auto merge = [](bool const, int const) -> char {
    return 'A';
  };

  STATIC_REQUIRE(optx::zip_with(none<bool>, none<int>, merge) == none<char>);
  STATIC_REQUIRE(optx::zip_with(std::optional{false}, none<int>, merge) ==
                 none<char>);
  STATIC_REQUIRE(optx::zip_with(none<bool>, std::optional{42}, merge) ==
                 none<char>);
  STATIC_REQUIRE(optx::zip_with(std::optional{false}, std::optional{42},
                                merge) == std::optional{'A'});
}

TEST_CASE("When both are engaged then pair them", "[zip]") {
  STATIC_REQUIRE(optx::zip(none<bool>, none<int>) ==
                 none<std::pair<bool, int>>);
  STATIC_REQUIRE(optx::zip(std::optional{false}, none<int>) ==
                 none<std::pair<bool, int>>);
  STATIC_REQUIRE(optx::zip(none<bool>, std::optional{42}) ==
                 none<std::pair<bool, int>>);
  STATIC_REQUIRE(optx::zip(std::optional{false}, std::optional{42}) ==
                 std::optional{std::pair{false, 42}});
}
