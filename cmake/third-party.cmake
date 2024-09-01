set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE BOOL "Don't fetch libraries everytime CMake runs")

# avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24+:
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()

include(FetchContent)

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
  find_package(Designar 2.0.1 REQUIRED)
else()
  FetchContent_Declare(
    Designar
    GIT_REPOSITORY https://github.com/3nity-studios/DeSiGNAR.git
    GIT_TAG        v2.0.1
    GIT_SHALLOW    ON
  )
  FetchContent_MakeAvailable(Designar)
endif()

if(RM_USE_SYSTEM_SFML)
  find_package(
    SFML 2.6
    COMPONENTS system window graphics audio
    REQUIRED
  )
else()
  FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        2.6.x
    GIT_SHALLOW    ON
    EXCLUDE_FROM_ALL
    SYSTEM
  )
  FetchContent_MakeAvailable(SFML)
endif()

if(RM_USE_SYSTEM_CATCH2)
  find_package(
    Catch2 3.7
    REQUIRED
  )
else()
  FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.7.0
    GIT_SHALLOW    ON
  )
  FetchContent_MakeAvailable(Catch2)
endif()
