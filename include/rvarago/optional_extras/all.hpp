#include <concepts>
#include <optional>

namespace rvarago::optional_extras {

// `filter(opt, pred)` is `opt` when `opt` is engaged and its value
// satisfies `pred`, otherwise is none.
template <typename T>
constexpr auto
filter(std::optional<T> opt,
       std::predicate<T> auto pred) noexcept -> std::optional<T> {
  if (opt && pred(*opt)) {
    return opt;
  } else {
    return std::optional<T>{};
  }
}

// `contains(opt, value)` is `true` when `opt` is engaged and its value
// equals `value`, otherwise is `false`.
template <typename T>
constexpr auto contains(std::optional<T> const &opt,
                        T const &value) noexcept -> bool {
  return static_cast<bool>(
      filter(opt, [&value](auto const &v) { return v == value; }));
}

} // namespace rvarago::optional_extras
