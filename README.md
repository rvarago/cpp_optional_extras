# cpp_optional_extras

A handful of utilities I wish [`optional<T>`](https://en.cppreference.com/w/cpp/utility/optional) had.

## Purpose

C++17 brought us `std::optional<T>`, then C++20 enhanced it with a couple of member-functions to safely express common transformations.

This library takes the next step and provides a handful of additional functions to make working with `optional<T>` even more ergonomic.

## Requirements

C++20

## Usage

This is a header-only library fully implemented in [`all.hpp`](include/rvarago/optional_extras/all.hpp).

- (Optional) Link against the INTERFACE `rvarago::optional_extras` target in your CMake build.
- Include `rvarago/optional_extras/all.hpp`
- Call into the functions inside the `rvarago::optional_extras` namespace, perhaps alias it as `namespace optx = rvarago::optional_extras;`

### Functions

- `contains(optional<T>, T) -> bool`
- `filter(optional<T>, T -> bool) -> optional<T>`

## Contributing

This repository has a [`flake.nix`](./flake.nix) with everything I need for development/CI (toolchain, language server, etc).

Furthermore, with:

```sh
nix develop -c check
```

You run all CI checks locally.
