cmake_minimum_required(VERSION 3.10)

project(MultiProject)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")

add_subdirectory(sort)
add_subdirectory(obuchaika)
add_subdirectory(lib/googletest googletest)
include_directories(lib/googletest/googletest/include)