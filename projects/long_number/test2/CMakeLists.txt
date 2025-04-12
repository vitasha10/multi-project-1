# Add the test executable
add_executable(ibusko_test ibusko_test_long_number.cpp)

# Link the test executable with the required libraries
target_link_libraries(ibusko_test
    PRIVATE
    gtest_main
    long_number
)

# Include the directory for the long_number library
target_include_directories(ibusko_test
    PRIVATE
    ${CMAKE_SOURCE_DIR}/projects/long_number/src
)

# Enable testing
enable_testing()

# Add the test to CTest
add_test(NAME ibusko_test COMMAND ibusko_test)
#add_executable(ibusko_test ${CMAKE_CURRENT_SOURCE_DIR}/test_long_number.cpp)