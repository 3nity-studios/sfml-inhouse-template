find_path(TMXLITE_INCLUDE_DIR NAMES tmxlite/Config.hpp PATH_SUFFIXES include)

find_library(TMXLITE_LIBRARY_DEBUG NAMES tmxlite-d)
find_library(TMXLITE_LIBRARY_RELEASE NAMES tmxlite)

include(SelectLibraryConfigurations)
select_library_configurations(TMXLITE)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(TMXLITE DEFAULT_MSG TMXLITE_LIBRARY TMXLITE_INCLUDE_DIR)
