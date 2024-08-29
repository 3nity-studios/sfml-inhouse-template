# gui

set(INCROOT ${PROJECT_SOURCE_DIR}/source/gui/include)
set(SRCROOT ${PROJECT_SOURCE_DIR}/source/gui/src)

set(
  SRC
  ${INCROOT}/state.hpp
  ${INCROOT}/main_menu_state.hpp
  ${SRCROOT}/main_menu_state.cpp
)
source_group("" FILES ${SRC})

add_library(
  route-master_gui OBJECT
  ${SRC}
)

target_include_directories(
  route-master_gui ${warning_guard}
  PUBLIC
  "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source/gui/include>"
)

target_compile_features(route-master_gui PUBLIC ${RM_REQUIRED_CXX})

target_link_libraries(
  route-master_gui
  PRIVATE
  sfml-graphics
)
