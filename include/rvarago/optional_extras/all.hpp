#include <concepts>
#include <optional>
#include <utility>

namespace rvarago::optional_extras {

// `filter(opt, pred)` is `opt` when `opt` is engaged and its value
// satisfies `pred`, otherwise is none.
template <typename T>
constexpr auto filter(std::optional<T> opt,
                      std::predicate<T> auto pred) noexcept
    -> std::optional<T> {
  if (opt && pred(*opt)) {
    return opt;
  } else {
    return std::optional<T>{};
  }
}

// `exists(opt, pred)` is `true` when `opt` is engaged and its
// value satisfies `pred`, otherwise is `false`
template <typename T>
constexpr auto exists(std::optional<T> const &opt,
                      std::predicate<T> auto pred) noexcept -> bool {
  return static_cast<bool>(filter(opt, pred));
}

// `contains(opt, value)` is `true` when `opt` is engaged and its value
// equals `value`, otherwise is `false`.
template <typename T>
constexpr auto contains(std::optional<T> const &opt, T const &value) noexcept
    -> bool {
  return exists(opt, [&value](auto const &v) { return v == value; });
}

// `zip_with(opt_lhs, opt_rhs, merge)` is an optional holding the outcome
// of applying `merge` to the values holded in `opt_lhs` and `opt_rhs`
// when both are engaged, otherwise is none.
template <typename L, typename R>
constexpr auto
zip_with(std::optional<L> opt_lhs, std::optional<R> opt_rhs,
         std::regular_invocable<L, R> auto
             merge) noexcept(noexcept(std::move(opt_lhs)) &&
                             noexcept(std::move(opt_rhs)) &&
                             noexcept(merge(*std::move(opt_lhs),
                                            *std::move(opt_rhs))))
    -> std::optional<decltype(merge(*std::move(opt_lhs),
                                    *std::move(opt_rhs)))> {
  if (opt_lhs && opt_rhs) {
    return std::optional{merge(*std::move(opt_lhs), *std::move(opt_rhs))};
  } else {
    return std::optional<decltype(merge(*std::move(opt_lhs),
                                        *std::move(opt_rhs)))>{};
  }
}

// `zip(opt_lhs, opt_rhs)` is an optional holding a pair
// with the values holded in `opt_lhs` and `opt_rhs`
// when both are engaged, otherwise is none.
template <typename L, typename R>
constexpr auto zip(std::optional<L> opt_lhs, std::optional<R> opt_rhs) noexcept(
    noexcept(std::move(opt_lhs)) && noexcept(std::move(opt_rhs)))
    -> std::optional<std::pair<L, R>> {
  return zip_with(std::move(opt_lhs), std::move(opt_rhs), std::make_pair<L, R>);
}

} // namespace rvarago::optional_extras
