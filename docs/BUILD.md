# Building Super Mario 2.0

The game is written in C++17 against **SFML 2.6** and built with CMake.

## Dependencies

- A C++17 compiler (clang or g++)
- CMake ≥ 3.16
- SFML 2.6 (graphics, window, system, audio)

### macOS

```sh
brew install sfml@2 cmake
```

`sfml@2` is keg-only; the `CMakeLists.txt` already adds the Homebrew prefix to
the search path, so no extra flags are needed.

### Ubuntu / Debian

```sh
sudo apt-get install -y cmake g++ libsfml-dev
```

## Build & run

From the `SuperMario 2.0/` directory (the one containing `CMakeLists.txt` and
the asset folders):

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
cd build && ./SuperMario2
```

The build copies the `Tiles/`, `Music/`, `Fonts/`, `Score/` folders and
`Coords.txt` next to the executable, so the game must be run from the `build/`
directory (or anywhere those assets sit alongside the binary).

## Continuous integration

`.github/workflows/build.yml` builds the project on Ubuntu and macOS for every
push and pull request, guaranteeing the tree always compiles.
