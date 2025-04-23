#include <catch2/catch_test_macros.hpp>

#include <optional>

#include <rvarago/optional_extras/wrapper.hpp>

namespace optx = rvarago::optional_extras;

using std::optional;

TEST_CASE("The wrapper delegates to already tested algorithms", "[smoke]") {
  constexpr auto got =
      optx::lift(optional{10}).zip_with(optional{20}, std::plus<>{}).get;
  STATIC_REQUIRE(got == optional{30});
}
