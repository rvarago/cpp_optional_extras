# cpp_optional_extras

A handful of C++ utilities I wish [`std::optional<T>`](https://en.cppreference.com/w/cpp/utility/optional) had.

## Purpose

C++17 brought us `std::optional<T>`, then C++20 enhanced it with a couple of member-functions to safely express common data transformations.

This library draws inspiration from other languages ​​and provides a handful of additional functions to make working with `std::optional<T>` even more ergonomic and less error-prone by encapsulating common patterns into reusable algorithms around correct access to the underlying `T`.

## Requirements

C++20

## Usage

This is a header-only library whose algorithms are in [`algorithm.hpp`](include/rvarago/optional_extras/algorithm.hpp).

- (Optional) Link against the INTERFACE `rvarago::optional_extras` target in your CMake build.
- Include `rvarago/optional_extras/algorithm.hpp`
- Call into the functions inside the `rvarago::optional_extras::algorithm` namespace, perhaps alias it as `namespace optx = rvarago::optional_extras::algorithm;`

### Functions

- `filter(optional<T>, T -> bool) -> optional<T>`
- `exists(optional<T>, T -> bool) -> bool`
- `contains(optional<T>, T) -> bool`
- `zip_with(optional<L>, optional<R>, (L, R) -> O) -> optional<O>`
- `zip(optional<L>, optional<R>) -> optional<pair<L, R>>`
- `unzip(optional<pair<L, R>) -> pair<optional<L>, optional<R>>`
- `append(optional<T>, optional<T>, (T, T) -> T) -> optional<T>`
- `fold(optional<T>, () -> R, T -> R) -> R`

## Contributing

This repository has a [`flake.nix`](./flake.nix) with everything I need for development/CI (toolchain, language server, etc).

Furthermore, with:

```sh
nix develop -c check
```

You run all CI checks locally.
