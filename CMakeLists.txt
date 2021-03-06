cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 11)
project(bitcoin-transaction-visualizer)

# This tells the compiler to not aggressively optimize and
# to include debugging information so that the debugger
# can properly read what's going on.
set(CMAKE_BUILD_TYPE Debug)

# Let's ensure -std=c++xx instead of -std=g++xx
set(CMAKE_CXX_EXTENSIONS OFF)

# Let's nicely support folders in IDE's
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Warning flags
if(MSVC)
    # warning level 3 and all warnings as errors
    add_compile_options(/W3 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wpedantic -Werror)
endif()

add_compile_options(-DDEBUG)

# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)

# FetchContent_MakeAvailable was not added until CMake 3.14
if(${CMAKE_VERSION} VERSION_LESS 3.14)
    include(cmake/add_FetchContent_MakeAvailable.cmake)
endif()

FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v2.x
)

FetchContent_Declare(
    boost
    URL https://boostorg.jfrog.io/artifactory/main/release/1.79.0/source/boost_1_79_0.zip
)

FetchContent_Declare(
    json 
    URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz
)

# Adds Catch2 testing library
FetchContent_GetProperties(catch2)
if(NOT catch2_POPULATED)
    FetchContent_Populate(catch2)
    add_library(catch2 INTERFACE)
    target_include_directories(catch2 INTERFACE ${catch2_SOURCE_DIR}/single_include)
endif()

# Adds json library
FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_library(json INTERFACE)
    target_include_directories(json INTERFACE ${json_SOURCE_DIR}/single_include)
endif()

# Adds boost library
FetchContent_GetProperties(boost)
if(NOT boost_POPULATED)
    FetchContent_Populate(boost)
    add_subdirectory(${boost_SOURCE_DIR} ${boost_BINARY_DIR})
endif()

find_package (Boost 1.55.0 REQUIRED COMPONENTS beast)

get_filename_component(CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../" ABSOLUTE)
get_filename_component(APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/" ABSOLUTE)

include("${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake")

list(APPEND CORE_SOURCE_FILES src/json.cc 
                              src/mass.cc
                              src/engine.cc
                              src/force.cc
                              src/renderables.cc
                              src/network.cc)

list(APPEND SOURCE_FILES    ${CORE_SOURCE_FILES}
                            src/visualizer.cc)

list(APPEND TEST_FILES  tests/test_json.cc
                        tests/test_engine.cc
                        tests/test_network.cc
                        tests/test_visualizer.cc)

ci_make_app(
        APP_NAME        visualizer
        CINDER_PATH     ${CINDER_PATH}
        SOURCES         apps/main.cc ${SOURCE_FILES}
        INCLUDES        include
        LIBRARIES       json beast
)

ci_make_app(
        APP_NAME        visualizer-test
        CINDER_PATH     ${CINDER_PATH}
        SOURCES         tests/test_main.cc ${SOURCE_FILES} ${TEST_FILES}
        INCLUDES        include
        LIBRARIES       catch2 json
)

if(MSVC)
    set_property(TARGET visualizer-test APPEND_STRING PROPERTY LINK_FLAGS " /SUBSYSTEM:CONSOLE")
endif()