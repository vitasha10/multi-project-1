cmake_minimum_required(VERSION 3.10)

project(MultiProject)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")

enable_testing()
add_subdirectory(projects/lib/googletest googletest)
include_directories(projects/lib/googletest/googletest/include)

add_subdirectory(projects/sort)
add_subdirectory(projects/obuchaika)
add_subdirectory(projects/long_number)
add_subdirectory(projects/linked_list)
add_subdirectory(projects/vector)