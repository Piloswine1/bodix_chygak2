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

find_package(Catch2)

if(Catch2_FOUND)
    include(CTest)
    include(Catch)

    add_executable(tests tests/test.cpp)
    target_link_libraries(tests Catch2::Catch2 bodix)
    catch_discover_tests(tests)
endif()


add_executable(main main.cpp)
target_link_libraries(main bodix)

target_compile_definitions(bodix PRIVATE BODIX_LIBRARY)
