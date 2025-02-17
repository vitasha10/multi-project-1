add_executable(test_bubble test_bubble.cpp)
target_link_libraries(test_bubble gtest_main bubble_sort_lib)
enable_testing()
add_test(NAME BubbleSortTest COMMAND test_bubble)