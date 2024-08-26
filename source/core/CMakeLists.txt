# this still needs to be well thought out to see how we're gonna manage modules

# module 1

set(INCROOT ${PROJECT_SOURCE_DIR}/source/core/module/include)
set(SRCROOT ${PROJECT_SOURCE_DIR}/source/core/module/src)

set(
  SRC
  ${SRCROOT}/lib.cpp
  ${INCROOT}/lib.hpp
)
source_group("" FILES ${SRC})

add_library(
  route-master_core OBJECT
  ${SRC}
)

target_include_directories(
  route-master_core ${warning_guard}
  PUBLIC
  "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source/core/module/include>"
)

# module 2...

target_compile_features(route-master_core PUBLIC ${RM_REQUIRED_CXX})
