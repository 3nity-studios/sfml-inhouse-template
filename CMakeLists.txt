cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)

# ---- Export compile commands for completion engines ----
set(CMAKE_EXPORT_COMPILE_COMMANDS=TRUE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# ---- Disabled as we're using presets ----
# set(CMAKE_CXX_STANDARD 17) # C++17
# set(CMAKE_CXX_STANDARD_REQUIRED ON) # is required
# set(CMAKE_CXX_EXTENSIONS OFF) # without compiler extensions like gnu++17

include(cmake/prelude.cmake)

# ---- Set project version and details ----
project(
    route-master
    VERSION 0.0.1
    DESCRIPTION "Route Master by Trinity Studios"
    HOMEPAGE_URL "https://github.com/3nity-studios/route-master"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Configurable options ----

option(RM_USE_SYSTEM_JSON "Use system's nlohmann's JSON library" OFF)
option(RM_USE_SYSTEM_DESIGNAR "Use system's DeSiGNAR library" OFF) # unused
option(RM_USE_SYSTEM_SFML "Use system's SFML library" OFF)

# ---- Third Party Dependencies ----

include(cmake/third-party.cmake)

# ---- Declare target ----

add_subdirectory(source)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

if(WIN32)
  add_custom_command(
    TARGET route-master_exe
    COMMENT "Copy OpenAL DLL"
    PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
    VERBATIM)
endif()

# ---- Developer mode ----

if(NOT RM_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for creating DEBUG builds of Route Master"
  )
endif()

include(cmake/dev-mode.cmake)
