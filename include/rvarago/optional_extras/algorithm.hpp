#include <concepts>
#include <functional>
#include <optional>
#include <type_traits>
#include <utility>

namespace rvarago::optional_extras::algorithm {

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
template <typename L, typename R, std::regular_invocable<L, R> BinaryFunction>
constexpr auto zip_with(
    std::optional<L> opt_lhs, std::optional<R> opt_rhs,
    BinaryFunction &&
        merge) noexcept(std::is_nothrow_move_constructible_v<L> &&
                        std::is_nothrow_move_constructible_v<R> &&
                        std::is_nothrow_invocable_v<BinaryFunction, L &&, R &&>)
    -> std::optional<std::invoke_result_t<BinaryFunction, L &&, R &&>> {
  if (opt_lhs && opt_rhs) {
    return std::optional{std::invoke(std::forward<BinaryFunction>(merge),
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

// `unzip(pair{opt_lhs, opt_rhs})` is a pair of optionals holding
// the values in `opt_lhs` and `opt_rhs`
// when both are engaged, otherwise is none.
template <typename L, typename R>
constexpr auto unzip(std::optional<std::pair<L, R>> opt_pair) noexcept(
    std::is_nothrow_move_constructible_v<L> &&
    std::is_nothrow_move_constructible_v<R>)
    -> std::pair<std::optional<L>, std::optional<R>> {
  if (opt_pair) {
    return std::make_pair(std::move(opt_pair->first),
                          std::move(opt_pair->second));
  } else {
    return std::make_pair(std::nullopt, std::nullopt);
  }
}

// `append(opt_lhs, opt_rhs, plus)` is an optional holding the outcome
// of applying `plus` to the values holded in `opt_lhs` and `opt_rhs`
// when both are engaged, otherwise is `opt_lhs` when that's engaged,
// otherwise is `opt_rhs`.
template <typename T,
          std::regular_invocable<T, T> BinaryOperator = std::plus<T>>
constexpr auto
append(std::optional<T> opt_lhs, std::optional<T> opt_rhs,
       BinaryOperator &&plus =
           {}) noexcept(std::is_nothrow_move_constructible_v<T> &&
                        std::is_nothrow_invocable_v<BinaryOperator, T &&, T &&>)
    -> std::optional<std::invoke_result_t<BinaryOperator, T &&, T &&>> {
  if (opt_lhs && opt_rhs) {
    return std::optional{std::invoke(std::forward<BinaryOperator>(plus),
                                     std::move(*opt_lhs), std::move(*opt_rhs))};
  } else if (opt_lhs) {
    return opt_lhs;
  } else {
    return opt_rhs;
  }
}

} // namespace rvarago::optional_extras::algorithm
