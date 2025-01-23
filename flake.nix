{
  description = "A handful of utilities I wish optional<T> had";

  inputs.nixpkgs.url = "nixpkgs/nixos-unstable";
  inputs.flake-utils.url = "github:numtide/flake-utils";
  outputs =
    {
      self,
      nixpkgs,
      flake-utils,
    }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = import nixpkgs { inherit system; };

        runCheck = pkgs.writeShellScriptBin "check" ''
          set -eu
          nixfmt --check flake.nix
          mdformat --check README.md
          prettier --check .github/workflows/*.yml
          cmake-format --check CMakeLists.txt test/CMakeLists.txt
          cmake-lint CMakeLists.txt test/CMakeLists.txt
          cmake -DRVARAGO_OPTIONAL_EXTRAS_WITH_TESTS=ON -S . -B build && cmake --build build --target check_all
        '';
      in
      {
        devShells = {
          default = pkgs.mkShell {
            buildInputs =
              [
                runCheck
              ]
              ++ [
                pkgs.nixd
                pkgs.nixfmt-rfc-style

                pkgs.nodePackages.prettier

                pkgs.mdformat

                pkgs.gcc
                pkgs.cmake
                pkgs.cmake-format
                pkgs.llvmPackages.clang-tools
                pkgs.catch2_3
              ];
          };
        };
      }
    );
}
