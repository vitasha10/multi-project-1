add_executable(long_number_tests tests.cpp)

target_link_libraries(long_number_tests PRIVATE long_number)
target_include_directories(long_number_tests PRIVATE ${CMAKE_SOURCE_DIR}/projects/long_number/src) 