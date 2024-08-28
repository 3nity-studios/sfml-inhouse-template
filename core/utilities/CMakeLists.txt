set(INCROOT ${PROJECT_SOURCE_DIR}/core/utilities/include)
set(SRCROOT ${PROJECT_SOURCE_DIR}/core/utilities/src)

set(
  SRC
  ${INCROOT}/filesystem.hpp
)
source_group("" FILES ${SRC})

add_library(
  route-master_utilities OBJECT
  ${SRC}
)

target_include_directories(
  route-master_utilities ${warning_guard}
  PUBLIC
  "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/core/utilities/include>"
)

target_compile_features(route-master_utilities PUBLIC ${RM_REQUIRED_CXX})
