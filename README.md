# std_optional_extras

A handful of utilities I wish [`std::optional<T>`](https://en.cppreference.com/w/cpp/utility/optional) had.

## Purpose

C++17 brought us `std::optional<T>`, then C++20 enhanced it with a couple of member-functions to safely express common transformations.

This library takes the next step and provides a handful of additional functions to make working with `optional<T>` even more ergonomic.

## Requirements

C++20

## Usage

This is a header-only library fully implemented in [`all.hpp`](include/rvarago/std_optional_extras/all.hpp).

- (Optional) Link against the INTERFACE `rvarago::std_optional_extras` target in your CMake build.
- Include `rvarago/std_optional_extras/all.hpp`
- Call into the functions inside the `rvarago::std_optional_extras` namespace, perhaps alias it as `namespace optx = rvarago::std_optional_extras;`

### filter(optional<t>, T -> bool) -> optional<T>

Given an optional and a unary predicate, return input optional when it's engaged with a value that satisfies the predicate, otherwise returns none.

## Contributing

This repository has a [`flake.nix`](./flake.nix) with everything I need for development/CI (toolchain, language server, etc).

Furthermore, with:

```sh
nix develop -c check
```

You run all CI checks locally.
