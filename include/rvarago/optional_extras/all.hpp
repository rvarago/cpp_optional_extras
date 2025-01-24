#include <concepts>
#include <functional>
#include <optional>
#include <type_traits>
#include <utility>

namespace rvarago::optional_extras {

// `filter(opt, pred)` is `opt` when `opt` is engaged and its value
// satisfies `pred`, otherwise is none.
template <typename T, std::predicate<T const &> Predicate>
constexpr auto filter(std::optional<T> opt, Predicate &&pred) noexcept(
    std::is_nothrow_invocable_v<Predicate, T const &>) -> std::optional<T> {
  if (opt && std::invoke(std::forward<Predicate>(pred), *opt)) {
    return opt;
  } else {
    return std::nullopt;
  }
}

// `exists(opt, pred)` is `true` when `opt` is engaged and its
// value satisfies `pred`, otherwise is `false`
template <typename T, std::predicate<T const &> Predicate>
constexpr auto exists(std::optional<T> const &opt, Predicate &&pred) noexcept(
    std::is_nothrow_invocable_v<Predicate, T const &>) -> bool {
  return opt && std::invoke(std::forward<Predicate>(pred), *opt);
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
template <typename L, typename R, std::regular_invocable<L, R> BinaryOperator>
constexpr auto zip_with(
    std::optional<L> opt_lhs, std::optional<R> opt_rhs,
    BinaryOperator &&
        merge) noexcept(std::is_nothrow_move_constructible_v<L> &&
                        std::is_nothrow_move_constructible_v<R> &&
                        std::is_nothrow_invocable_v<BinaryOperator, L &&, R &&>)
    -> std::optional<std::invoke_result_t<BinaryOperator, L &&, R &&>> {
  if (opt_lhs && opt_rhs) {
    return std::optional{std::invoke(std::forward<BinaryOperator>(merge),
                                     std::move(*opt_lhs), std::move(*opt_rhs))};
  } else {
    return std::nullopt;
  }
}

// `zip(opt_lhs, opt_rhs)` is an optional holding a pair
// with the values holded in `opt_lhs` and `opt_rhs`
// when both are engaged, otherwise is none.
template <typename L, typename R>
constexpr auto zip(std::optional<L> opt_lhs, std::optional<R> opt_rhs) noexcept(
    std::is_nothrow_move_constructible_v<L> &&
    std::is_nothrow_move_constructible_v<R>) -> std::optional<std::pair<L, R>> {
  return zip_with(std::move(opt_lhs), std::move(opt_rhs), std::make_pair<L, R>);
}

} // namespace rvarago::optional_extras
