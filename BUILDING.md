# Building 

If you want to contribute as fast as possible, you can spin up a DevContainer
and start developing right away with our Dockerfile (that is on the works).

Otherwise, keep on reading to know how to match the needed development environment.

## Dependencies Setup

There are a few options that you can modify in CMakeLists.txt like:

|             Option              |      Type      |                            Description                              |
|         :-------------:         | :------------- |                          :-------------                             |
| `RM_USE_EXTERNAL_JSON`          | BOOL           | Turn ON to use system's installation of nlohmann's JSON             |
| `RM_USE_EXTERNAL_DESIGNAR`      | BOOL           | Turn ON to use system's installation of DeSiGNAR (unused)           |
| `RM_USE_EXTERNAL_SFML`          | BOOL           | Turn ON to use system's installation of SFML                        |

If you opt for not using the libraries installed in your system, then you must
install development dependencies in order to build the libraries when
configuring the project. (Note: DeSiGNAR is always downloaded as we roll a
slightly modified version of the library)

To build SFML on Linux you will need:
* XRandr
* XCursor
* UDev
* Freetype
* OpenAL
* FLAC
* Vorbis
* GL1-Mesa
* EGL1-Mesa

These are some goodies that we use in our [workflow][3]:
* doxygen 1.8.20
* clang-format
* clang-tidy
* cppcheck

### Linux (Debian-based) SFML dependencies

```shell
sudo apt update
sudo apt install \
    libxrandr-dev \
    libxcursor-dev \
    libudev-dev \
    libfreetype-dev \
    libopenal-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev
```

### Linux (Debian-based) Route Master dependencies

These probably aren't strictly necessary to build the project but they provide
Quality-of-Life features worth trying.

```shell
sudo apt update
sudo apt install \
    clang-format \
    clang-tidy \
    cppcheck \
    libfreetype-dev \
    libopenal-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev
```

TODO: Add LCOV, codespell and Doxygen 1.8.20 installation if they're gonna be
used.

### Other systems

Have simply not been tested.

## Build

This project doesn't require any special command-line flags to build to keep
things simple.

Here are the steps for building in release mode:

```sh
cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
cmake --build build
```

An executable should be generated somewhere in the build folder (presumably
in the build/source folder)

### ~~Building with MSVC~~

~~Note that MSVC by default is not standards compliant and you need to pass some~~
~~flags to make it behave properly. See the `flags-msvc` preset in the~~
~~[CMakePresets.json](CMakePresets.json) file for the flags and with what~~
~~variable to provide them to CMake during configuration.~~

### ~~Building on Apple Silicon~~

~~CMake supports building on Apple Silicon properly since 3.20.1. Make sure you~~
~~have the [latest version][1] installed.~~

## Install

This project doesn't require any special command-line flags to install to keep
things simple. As a prerequisite, the project has to be built with the above
commands already.

Here is the command for installing the release mode artifacts, although no
install rules have been defined for the moment, we plan on keeping things
portable before delving into installing shenanigans (see --prefix CMake flag).

```sh
cmake --install build
```

## Notes

### Shout-out

The mentioned goodies are simply not necessary in order to build the project
(a C++17 compatible compiler, SFML, DeSiGNAR, and nlohmann's JSON should
suffice).

Most of the tools mentioned were simply adopted as a by-product of using the
incredible template provided by [cmake-init][3]

### Room for improvement

We could probably write a script that automatically pulls all the dependencies
and installs them in the system. (Besides CMake fetching some libraries).

A Dockerfile with batteries included is on the works.

> [WARNING]
> Building on other systems nor cross-compiling have been tested. Don't expect
> things to work fluidly just yet. Although we'd love to port Route Master to Windows


[1]: https://cmake.org/download/
[2]: https://cmake.org/cmake/help/latest/manual/cmake.1.html#install-a-project
[3]: https://github.com/friendlyanon/cmake-init/
