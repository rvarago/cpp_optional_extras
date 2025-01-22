#include <concepts>
#include <optional>

namespace rvarago::std_optional_extras {

// `filter(opt, pred)` is `opt` when `opt` is engaged and its value
// satisfies `pred`, otherwise is none.
template <typename T>
constexpr auto filter(std::optional<T> opt, std::predicate<T> auto pred)
    -> std::optional<T> {
  if (opt && pred(*opt)) {
    return opt;
  } else {
    return std::nullopt;
  }
}

// `contains(opt, value)` is `true` when `opt` is engaged and its value
// equals `value`, otherwise is `false`.
template <typename T>
constexpr auto contains(std::optional<T> const &opt, T const &value) -> bool {
  return filter(opt, [&value](auto const &v) { return v == value; })
      .has_value();
}

} // namespace rvarago::std_optional_extras
