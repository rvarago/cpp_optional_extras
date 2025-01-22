#include <catch2/catch_test_macros.hpp>

#include <rvarago/std_optional_extras/all.hpp>

namespace optx = rvarago::std_optional_extras;

TEST_CASE("id is identity", "[id]") { static_assert(optx::id(42) == 42); }
