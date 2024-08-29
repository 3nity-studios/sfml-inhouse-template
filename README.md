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

For a smooth experience, you can open the repository in Visual Studio Code with
the DevContainer extension and start developing right away.

Otherwise, keep on reading to know how to match the needed development
environment.

> [WARNING]
> Neither building on other systems nor cross-compiling is supported for the
> moment.

### Prerequisites

System and compiler:
* Linux (Debian 11 or newer)
* gcc (10 or newer) / clang (11 or newer)

Note: this are the minimum versions on which the project's build process has
been currently tested. Nonetheless, theoretically speaking, it should suffice
with a C++17 compatible compiler.

Libraries:
* SFML
* DeSiGNAR
* nlohmann's json

Note that to build SFML on Linux you will need the development packages of:
* XRandr
* XCursor
* UDev
* Freetype
* OpenAL
* FLAC
* Vorbis
* GL1-Mesa
* EGL1-Mesa

(Optional) These are some goodies that we use in the development of our project:
* clang-format
* clang-tidy
* cppcheck
* codespell

#### Installing dependencies

If you opt for not using the libraries installed in your system (see setup
section below), then you must install development dependencies in order to build
the libraries when configuring the project.
(Note: DeSiGNAR is always downloaded as we roll a slightly modified version of
this library)

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

As said, these aren't strictly necessary to build the project but they provide
some Quality-of-Life features for development worth trying.

```shell
sudo apt update
sudo apt install \
    clang-format \
    clang-tidy \
    cppcheck \
    python3-pip
python3 -m pip install codespell
```

### Setup

Before diving into building, you must know that there are a few options that you
can modify in CMakeLists.txt (or in CMakeCache with ccmake/cmake-gui), like:

|             Option              |      Type      |                             Description                             |
|         :-------------:         | :------------- |                           :-------------                            |
| `RM_USE_SYSTEM_JSON`            | BOOL           | Turn ON to use system's installation of nlohmann's JSON             |
| `RM_USE_SYSTEM_DESIGNAR`        | BOOL           | Turn ON to use system's installation of DeSiGNAR                    |
| `RM_USE_SYSTEM_SFML`            | BOOL           | Turn ON to use system's installation of SFML                        |
| `RM_DEVELOPER_MODE`             | BOOL           | Turn ON to enable tests and developer targets of Route Master       |

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

That's it! From here on, there are some tips for developing.

## Developer information

Build system targets that are only useful for developers of this project are
hidden if the `RM_DEVELOPER_MODE` option is disabled. Enabling this
option makes tests and other developer targets and options available. Not
enabling this option means that you are a consumer of this project and thus you
have no need for these targets and options (or you just wanna build a production
release).

~~Developer mode is always set to on in CI workflows.~~ No workflows have been
set up for the time being. Plans on this are underway.

### Presets

This project makes use of [presets][1] to simplify the process of configuring
the project. As a developer, you are recommended to always have the [latest
CMake version][2] installed to make use of the latest Quality-of-Life
additions.

You should create a `CMakeUserPresets.json` file at the root of the project.

For example, here's the one we're currently using:

```json
{
  "version": 8,
  "cmakeMinimumRequired": {
    "major": 3,
    "minor": 30,
    "patch": 2
  },
  "configurePresets": [
    {
      "name": "dev-common",
      "hidden": true,
      "inherits": ["dev-mode", "clang-tidy", "cppcheck"],
      "cacheVariables": {
        "BUILD_MCSS_DOCS": "ON"
      }
    },
    {
      "name": "dev-linux",
      "binaryDir": "${sourceDir}/build/dev-linux",
      "inherits": ["dev-common", "ci-linux"],
      "cacheVariables": {
        "CMAKE_BUILD_TYPE": "Debug",
        "CMAKE_EXPORT_COMPILE_COMMANDS": "ON"
      }
    },
    {
      "name": "dev-darwin",
      "binaryDir": "${sourceDir}/build/dev-darwin",
      "inherits": ["dev-common", "ci-darwin"]
    },
    {
      "name": "dev-win64",
      "binaryDir": "${sourceDir}/build/dev-win64",
      "inherits": ["dev-common", "ci-win64"],
      "environment": {
        "UseMultiToolTask": "true",
        "EnforceProcessCountAcrossBuilds": "true"
      }
    },
    {
      "name": "dev",
      "binaryDir": "${sourceDir}/build/dev",
      "inherits": "dev-linux",
      "cacheVariables": {
        "RM_USE_SYSTEM_JSON": "TRUE",
        "RM_USE_SYSTEM_DESIGNAR": "TRUE",
        "RM_USE_SYSTEM_SFML": "TRUE"
      }
    },
    {
      "name": "dev-coverage",
      "binaryDir": "${sourceDir}/build/coverage",
      "inherits": ["dev-mode", "coverage-linux"]
    }
  ],
  "buildPresets": [
    {
      "name": "dev",
      "configurePreset": "dev",
      "configuration": "Debug",
      "jobs": 2
    },
    {
      "name": "dev-linux",
      "configurePreset": "dev-linux",
      "configuration": "Debug",
      "jobs": 2
    }
  ],
  "testPresets": [
    {
      "name": "dev",
      "configurePreset": "dev",
      "configuration": "Debug",
      "output": {
        "outputOnFailure": true
      },
      "execution": {
        "jobs": 2,
        "noTestsAction": "error"
      }
    }
  ]
}
```

We currently have no plans for building on platforms
other than Linux. There might be intents of cross-compiling in a future but
that's just not a priority right now.

`CMakeUserPresets.json` is also the perfect place in which you can put all
sorts of things that you would otherwise want to pass to the configure command
in the terminal.

See the [presets documentation][1] if you want to go down that rabbit hole.

**Note**: Visual Studio Code is a great editor that can help you with this step!

### Configure, build and test

If you followed the above instructions, then you can configure, build and test
the project respectively with the following commands from the project root on
any operating system with any build system:

```sh
cmake -S . -B build --preset=dev-linux
cmake --build build --preset=dev-linux
ctest --preset=dev-linux
```

If you are using a compatible editor you can select the above created presets
for automatic integration, neat! Isn't?

### Developer mode targets

These are targets you may invoke using the build command from above, with an
additional `-t <target>` flag
(for example `cmake --build build/dev-linux/ --target format-check`).

#### ~~`coverage`~~

Yeah... no tests.

~~Available if `ENABLE_COVERAGE` is enabled. This target processes the output of~~
~~the previously run tests when built with coverage configuration. The commands~~
~~this target runs can be found in the `COVERAGE_TRACE_COMMAND` and~~
~~`COVERAGE_HTML_COMMAND` cache variables. The trace command produces an info~~
~~file by default, which can be submitted to services with CI integration. The~~
~~HTML command uses the trace command's output to generate an HTML document to~~
~~`<binary-dir>/coverage_html` by default.~~

#### `format-check` and `format-fix`

These targets run the clang-format tool on the codebase to check errors and to
fix them respectively. Customization available using the `FORMAT_PATTERNS` and
`FORMAT_COMMAND` cache variables.

#### `run-exe`

Runs the executable target `route-master_exe`.

#### `spell-check` and `spell-fix`

These targets run the codespell tool on the codebase to check errors and to fix
them respectively. Customization available using the `SPELL_COMMAND` cache
variable. We configured it to ignore CMakeLists files and uppercase words.

### Note

So far, for development, only Visual Studio Code with [clangd extension][3] has
been properly tested. If you want to have code completion and get rid of
unresolved includes you need to run cmake with `-DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE`
if you're not using the development presets (`dev-*`)

## Contributing

See the [CONTRIBUTING](CONTRIBUTING.md) document.

## Acknowledgments

These are the great projects that make all of this possible:

* [DeSiGNAR](https://github.com/R3mmurd/DeSiGNAR)
* [SFML](https://github.com/SFML/SFML)
* [JSON for Modern C++](https://github.com/nlohmann/json)
* [cmake-sfml-project](https://github.com/SFML/cmake-sfml-project)
* [cmake-sfml-demo](https://github.com/danebulat/cmake-sfml-demo)
* [cmake-init](https://github.com/friendlyanon/cmake-init)
* [Doxygen](https://github.com/doxygen/doxygen)


[1]: https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html
[2]: https://cmake.org/download/
[3]: https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-clangd
