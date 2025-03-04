# cpp_optional_extras

A handful of C++ utilities I wish [`std::optional<T>`](https://en.cppreference.com/w/cpp/utility/optional) had.

## Purpose

C++17 brought us `std::optional<T>`, then C++23 enhanced it with a couple of member-functions (e.g. `transform`) to safely express common data transformations.

This library draws inspiration from other languages ​​and provides a handful of additional functions to make working with `std::optional<T>` even more ergonomic and less error-prone by encapsulating common patterns into reusable algorithms around correct access to the underlying `T`.

### Examples

You have an function `get_access_token` that returns an `access_token` and you want to `verify_signature` and do something when it's valid. With `exists`:

```cpp
auto get_access_token() -> std::optional<access_token>;
auto verify_signature(access_token const &) -> bool;

if (optx::exists(get_access_token(), verify_signature)) {
    // do something
}
```

You have a `person` with optional `first_name` and `second_name`, and you want to format them when both are available or return the first available one, otherwise return `N/A` when neither is available. With `append`:

```cpp
struct person {
  std::optional<std::string> first_name;
  std::optional<std::string> second_name;

  auto format_name() const -> std::string {
    return optx::append(first_name, second_name,
                        [](auto const fname, auto const sname) {
                          return fname + " " + sname;
                        })
        .value_or(std::string{"N/A"});
  }
};
```

These are just two of the available algorithms!

### Functions

- `filter(optional<T>, T -> bool) -> optional<T>`
- `exists(optional<T>, T -> bool) -> bool`
- `contains(optional<T>, T) -> bool`
- `zip_with(optional<L>, optional<R>, (L, R) -> O) -> optional<O>`
- `zip(optional<L>, optional<R>) -> optional<pair<L, R>>`
- `unzip(optional<pair<L, R>) -> pair<optional<L>, optional<R>>`
- `append(optional<T>, optional<T>, (T, T) -> T) -> optional<T>`
- `fold(optional<T>, () -> R, T -> R) -> R`

## Requirements

C++20

## Usage

This is a header-only library. Algorithms live in [`algorithm.hpp`](include/rvarago/optional_extras/algorithm.hpp).

- (Optional) Link against the INTERFACE `rvarago::optional_extras` target in your CMake build.
- Include `rvarago/optional_extras/algorithm.hpp`
- Call into functions from the `rvarago::optional_extras::algorithm` namespace, perhaps alias it as `namespace optx = rvarago::optional_extras::algorithm;` to save keystrokes.

## Contributing

This repository has a [`flake.nix`](./flake.nix) with everything I need for development/CI (toolchain, language server, etc).

Furthermore, with:

```sh
nix develop -c check
```

You run all CI checks locally.
