#include <optional>
#include <utility>

#include "algorithm.hpp"

namespace rvarago::optional_extras {

template <typename T> struct optional_wrapper {

  template <std::predicate<T const &> Predicate>
  constexpr auto filter(Predicate &&pred) && noexcept(noexcept(
      algorithm::filter(std::declval<std::optional<T> &&>(),
                        std::declval<Predicate &&>()))) -> optional_wrapper<T> {
    return optional_wrapper{
        algorithm::filter(std::move(get), std::forward<Predicate>(pred))};
  }

  template <typename R, std::regular_invocable<T, R> BinaryFunction>
  constexpr auto
  zip_with(std::optional<R> rhs, BinaryFunction &&merge) && noexcept(
      noexcept(algorithm::zip_with(
          std::declval<std::optional<T> &&>(),
          std::declval<std::optional<R> &&>(),
          std::forward<BinaryFunction>(std::declval<BinaryFunction &&>()))))
      -> optional_wrapper<std::invoke_result_t<BinaryFunction, T &&, R &&>> {
    return optional_wrapper{algorithm::zip_with(
        std::move(get), std::move(rhs), std::forward<BinaryFunction>(merge))};
  }

  template <typename R>
  constexpr auto zip(std::optional<R> rhs) && noexcept(
      noexcept(algorithm::zip(std::declval<std::optional<T> &&>(),
                              std::declval<std::optional<R> &&>())))
      -> optional_wrapper<std::pair<T, R>> {
    return optional_wrapper{algorithm::zip(std::move(get), std::move(rhs))};
  }

  std::optional<T> get;
};

template <typename T>
constexpr auto lift(std::optional<T> inner) -> optional_wrapper<T> {
  return optional_wrapper<T>{std::move(inner)};
}

} // namespace rvarago::optional_extras
