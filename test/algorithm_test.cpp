#include <catch2/catch_test_macros.hpp>

#include <optional>
#include <utility>

#include <rvarago/optional_extras/algorithm.hpp>

namespace optx = rvarago::optional_extras::algorithm;

using std::optional;
using std::pair;

template <typename T> constexpr optional<T> none{std::nullopt};

TEST_CASE(
    "When engaged with a value satisfying a predicate passes input through",
    "[filter]") {
  static constexpr auto is_even = [](int const x) -> bool {
    return (x % 2) == 0;
  };

  STATIC_REQUIRE(optx::filter(none<int>, is_even) == none<int>);
  STATIC_REQUIRE(optx::filter(optional{1}, is_even) == none<int>);
  STATIC_REQUIRE(optx::filter(optional{42}, is_even) == optional{42});
}

TEST_CASE("When engaged with a value satisfying a predicate", "[exists]") {
  static constexpr auto is_even = [](int const x) -> bool {
    return (x % 2) == 0;
  };

  STATIC_REQUIRE(optx::exists(none<int>, is_even) == false);
  STATIC_REQUIRE(optx::exists(optional{1}, is_even) == false);
  STATIC_REQUIRE(optx::exists(optional{42}, is_even) == true);
}

TEST_CASE("When engaged with a value equal to the argument", "[contains]") {
  STATIC_REQUIRE(optx::contains(none<int>, 42) == false);
  STATIC_REQUIRE(optx::contains(optional{1}, 42) == false);
  STATIC_REQUIRE(optx::contains(optional{42}, 42) == true);
}

TEST_CASE("When both are engaged then merge them", "[zip_with]") {
  static constexpr auto merge = [](bool const, int const) -> char {
    return 'A';
  };

  STATIC_REQUIRE(optx::zip_with(none<bool>, none<int>, merge) == none<char>);
  STATIC_REQUIRE(optx::zip_with(optional{false}, none<int>, merge) ==
                 none<char>);
  STATIC_REQUIRE(optx::zip_with(none<bool>, optional{42}, merge) == none<char>);
  STATIC_REQUIRE(optx::zip_with(optional{false}, optional{42}, merge) ==
                 optional{'A'});
}

TEST_CASE("When both are engaged then pair them", "[zip]") {
  STATIC_REQUIRE(optx::zip(none<bool>, none<int>) == none<pair<bool, int>>);
  STATIC_REQUIRE(optx::zip(optional{false}, none<int>) ==
                 none<pair<bool, int>>);
  STATIC_REQUIRE(optx::zip(none<bool>, optional{42}) == none<pair<bool, int>>);
  STATIC_REQUIRE(optx::zip(optional{false}, optional{42}) ==
                 optional{pair{false, 42}});
}

TEST_CASE(
    "When both are engaged append them or return the first engaged or none",
    "[append]") {
  constexpr auto mul = [](int const lhs, int const rhs) -> int {
    return lhs * rhs;
  };

  STATIC_REQUIRE(optx::append(none<int>, none<int>, mul) == none<int>);
  STATIC_REQUIRE(optx::append(none<int>, optional{3}, mul) == optional{3});
  STATIC_REQUIRE(optx::append(optional{2}, none<int>, mul) == optional{2});
  STATIC_REQUIRE(optx::append(optional{2}, optional{3}, mul) == optional{6});
}
