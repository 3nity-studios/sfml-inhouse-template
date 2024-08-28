# Hacking

Here is some wisdom to help you build and test this project as a developer and
potential contributor. (Not that we are expecting more contributors whatsoever)

If you plan to contribute, please read the [CONTRIBUTING](CONTRIBUTING.md)
guide, we have some really cool guidelines to follow there.

## Developer mode

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

As a developer, you should create a `CMakeUserPresets.json` file at the root of
the project:

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
      "inherits": "dev-linux"
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

It needs to be purged as we currently have no plans for building on platforms
other than Linux. There might be intents of cross-compiling in a future but
that's just not a priority right now.

`CMakeUserPresets.json` is also the perfect place in which you can put all
sorts of things that you would otherwise want to pass to the configure command
in the terminal.

See the [presets documentation][1] if you want to go down that rabbit hole.

> **Note**
> Visual Studio Code is a great editor that can help you with this step!

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

#### `coverage`

Yeah... no tests.

~~Available if `ENABLE_COVERAGE` is enabled. This target processes the output of~~
~~the previously run tests when built with coverage configuration. The commands~~
~~this target runs can be found in the `COVERAGE_TRACE_COMMAND` and~~
~~`COVERAGE_HTML_COMMAND` cache variables. The trace command produces an info~~
~~file by default, which can be submitted to services with CI integration. The~~
~~HTML command uses the trace command's output to generate an HTML document to~~
~~`<binary-dir>/coverage_html` by default.~~

#### ~~`docs`~~

Yeah... no docs either.

~~Available if `BUILD_MCSS_DOCS` is enabled. Builds to documentation using~~
~~Doxygen and m.css. The output will go to `<binary-dir>/docs` by default~~
~~(customizable using `DOXYGEN_OUTPUT_DIRECTORY`).~~

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

## Note

So far only Visual Studio Code with [clangd extension](https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-clangd)
has been tested. If you want to have Intellisense and get rid of unresolved
includes you need to run cmake with `-DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE`
if you're not using the development presets (`dev-*`)

[1]: https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html
[2]: https://cmake.org/download/
