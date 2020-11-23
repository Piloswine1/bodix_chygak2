cmake_minimum_required(VERSION 3.14)

project(bodix LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(bodix SHARED
  bodix_global.h
  bodix.cpp
  bodix.hpp
)

find_package(Catch2 REQUIRED)

if(Catch2_FOUND)
    add_executable(test tests/test.cpp)
    target_link_libraries(test Catch2::Catch2 bodix)
    add_test(all_test test)
endif()

add_executable(main main.cpp)
target_link_libraries(main bodix)

target_compile_definitions(bodix PRIVATE BODIX_LIBRARY)
