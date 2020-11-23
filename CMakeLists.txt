cmake_minimum_required(VERSION 3.14)

project(bodix LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(bodix SHARED
  bodix_global.h
  bodix.cpp
  bodix.hpp
)

find_package(Catch2 QUIET)

if(NOT Catch2_FOUND)
    Include(FetchContent)

    FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG        v2.13.1
    )

    FetchContent_MakeAvailable(Catch2)
endif()

include(CTest)
include(Catch)

add_executable(tests tests/test.cpp)
target_link_libraries(tests Catch2::Catch2 bodix)
catch_discover_tests(tests)

add_executable(main main.cpp)
target_link_libraries(main bodix)

target_compile_definitions(bodix PRIVATE BODIX_LIBRARY)
