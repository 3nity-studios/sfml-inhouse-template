# ---- Only tested with CMake 3.30.2 at the moment ----
cmake_minimum_required(VERSION 3.30.2)

# I don't have the slightest idea what this does. But it doesn't hurt c:
include(${PROJECT_SOURCE_DIR}/cmake/folders.cmake)

# ---- Set options ----

set(RM_REQUIRED_CXX "cxx_std_17")
set(RM_OS_LINUX TRUE)
# we are working on porting a macro that detects the OS, Linux is the default
# for now.

# ---- Declare modules ----

include_directories(${PROJECT_SOURCE_DIR}/source)
include_directories(${PROJECT_SOURCE_DIR}/source/include)

# core

add_subdirectory(core)

# engine

add_subdirectory(engine)

# gui

add_subdirectory(gui)

# platform

add_subdirectory(platform)

# states

add_subdirectory(states)

# utilities

add_subdirectory(utilities)

# ---- Declare source files ----

set(INCROOT ${PROJECT_SOURCE_DIR}/source/include)
set(SRCROOT ${PROJECT_SOURCE_DIR}/source)

# One could argue that a GLOB might suit us better
set(
  SRC
  ${INCROOT}/global.hpp
  ${INCROOT}/game.hpp
  ${SRCROOT}/game.cpp
  ${INCROOT}/config.hpp
  ${SRCROOT}/config.cpp
  ${SRCROOT}/main.cpp
)
source_group("" FILES ${SRC})

# ---- Declare executable ----

add_executable(route-master_exe ${SRC})
add_executable(route-master::exe ALIAS route-master_exe)

set_property(TARGET route-master_exe PROPERTY OUTPUT_NAME route-master)

target_compile_features(route-master_exe PRIVATE ${RM_REQUIRED_CXX})

target_link_libraries(
  route-master_exe
  PRIVATE
  route-master_platform
  route-master_utilities
  route-master_engine
  route-master_core
  route-master_gui
  route-master_states
  nlohmann_json::nlohmann_json
  Designar
)

# ---- End-of-file commands ----

add_folders(Source)
