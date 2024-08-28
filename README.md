<h1 align="center">Route Master</h1>

![cpp-badge](https://img.shields.io/badge/C%2B%2B%2017-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![cmake-badge](https://img.shields.io/badge/CMake_3.30.2-064F8C?style=for-the-badge&logo=cmake&logoColor=white)
![sfml-badge](https://img.shields.io/badge/SFML_2.6.1-4BB000?style=for-the-badge&logo=sfml&logoColor=white)
![designar-badge](https://img.shields.io/badge/DeSiGNAR_2.0.1-2A2A2A?style=for-the-badge)
![conventionalcommits-badge](https://img.shields.io/badge/Conventional_Commits_1.0.0-FE5196?style=for-the-badge&logo=conventionalcommits&logoColor=white)

## Intro

Route Master is a simulation game where you manage a bus company, try to grow
your earnings by testing different routes, upgrading your fleet or taking
risks by signing contracts. Your goal is to become a tycoon in the urban
transport sector!

## Building and installing

If you want to contribute as fast as possible, you can spin up a DevContainer
and start developing right away with our Dockerfile (that is on the works).

Otherwise, keep on reading to know how to match the needed development environment.

### Dependencies Setup

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

#### Linux (Debian-based) SFML dependencies

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

#### Linux (Debian-based) Route Master dependencies

These probably aren't strictly necessary to build the project but they provide
Quality-of-Life features worth trying.

```shell
sudo apt update
sudo apt install \
    clang-format \
    clang-tidy \
    cppcheck \
    libsfml-dev \
    libfreetype-dev \
    libopenal-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev
```

TODO: Add LCOV, codespell and Doxygen 1.8.20 installation if they're gonna be
used.

#### Other systems

Have simply not been tested.

### Build

This project doesn't require any special command-line flags to build to keep
things simple.

Here are the steps for building in release mode:

```sh
cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
cmake --build build
```

An executable should be generated somewhere in the build folder (presumably
in the build/source folder)

#### ~~Building with MSVC~~

~~Note that MSVC by default is not standards compliant and you need to pass some~~
~~flags to make it behave properly. See the `flags-msvc` preset in the~~
~~[CMakePresets.json](CMakePresets.json) file for the flags and with what~~
~~variable to provide them to CMake during configuration.~~

#### ~~Building on Apple Silicon~~

~~CMake supports building on Apple Silicon properly since 3.20.1. Make sure you~~
~~have the [latest version][1] installed.~~

### Install

This project doesn't require any special command-line flags to install to keep
things simple. As a prerequisite, the project has to be built with the above
commands already.

Here is the command for installing the release mode artifacts, although no
install rules have been defined for the moment, we plan on keeping things
portable before delving into installing shenanigans (see --prefix CMake flag).

```sh
cmake --install build
```

### Notes

#### Shout-out

The mentioned goodies are simply not necessary in order to build the project
(a C++17 compatible compiler, SFML, DeSiGNAR, and nlohmann's JSON should
suffice).

Most of the tools mentioned were simply adopted as a by-product of using the
incredible template provided by [cmake-init][3]

#### Room for improvement

We could probably write a script that automatically pulls all the dependencies
and installs them in the system. (Besides CMake fetching some libraries).

A Dockerfile with batteries included is on the works.

> [WARNING]
> Building on other systems nor cross-compiling have been tested. Don't expect
> things to work fluidly just yet. Although we'd love to port Route Master to Windows


[1]: https://cmake.org/download/
[2]: https://cmake.org/cmake/help/latest/manual/cmake.1.html#install-a-project
[3]: https://github.com/friendlyanon/cmake-init/


## Contributing

See the [CONTRIBUTING](CONTRIBUTING.md) document.

## Acknowledgments

These are the great projects that make all of this possible:

* [DeSiGNAR](https://github.com/R3mmurd/DeSiGNAR)
* [SFML](https://github.com/SFML/SFML)
* [JSON for Modern C++](https://github.com/nlohmann/json)
* [cmake-sfml-project](https://github.com/SFML/cmake-sfml-project)
* [cmake-init](https://github.com/friendlyanon/cmake-init)
* [Doxygen](https://github.com/doxygen/doxygen)
