cmake_minimum_required(VERSION 3.10)

project(obuchaika)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(obuchaika_app
    main.cpp
    menu_functions.cpp
    menu_items.cpp
)

target_include_directories(obuchaika_app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})