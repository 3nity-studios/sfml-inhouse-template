set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE BOOL "Don't fetch libraries everytime CMake runs")

include(FetchContent)

# actually, all the find_package() lines have gone untested so far.

if(RM_USE_SYSTEM_JSON)
  find_package(nlohmann_json 3.11.3 REQUIRED)
else()
  FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
  )
  FetchContent_MakeAvailable(json)
endif()

if(RM_USE_SYSTEM_DESIGNAR) # one can only dream huh? c:
  find_package(designar 2.0.1 REQUIRED)
else()
  FetchContent_Declare(
    designar
    GIT_REPOSITORY https://github.com/3nity-studios/DeSiGNAR.git
    GIT_TAG v2.0.1
  )
  FetchContent_MakeAvailable(designar)
endif()

if(RM_USE_SYSTEM_SFML)
  find_package(
    SFML 2.5 # should be 2.6.1
    COMPONENTS system window graphics audio
    REQUIRED
  )
else()
  FetchContent_Declare(
    sfml
    # GIT_REPOSITORY https://github.com/SFML/SFML.git
    # GIT_TAG 2.6.x
    URL https://github.com/SFML/SFML/archive/refs/tags/2.6.1.zip # smaller
    EXCLUDE_FROM_ALL
    SYSTEM
  )
  FetchContent_MakeAvailable(sfml)
endif()
