#include "bubble_sort.hpp"
#include <gtest/gtest.h>

TEST(BubbleSortTest, SortedArray) {
    int arr[] = {1, 2, 3, 4, 5};
    const int size = sizeof(arr) / sizeof(arr[0]);

    bubble_sort(arr, size);

    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 4);
    EXPECT_EQ(arr[4], 5);
}

TEST(BubbleSortTest, UnsortedArray) {
    int arr[] = {5, 3, 4, 1, 2};
    const int size = sizeof(arr) / sizeof(arr[0]);

    bubble_sort(arr, size);

    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 4);
    EXPECT_EQ(arr[4], 5);
}

TEST(BubbleSortTest, EmptyArray) {
    int* arr = nullptr;
    const int size = 0;

    bubble_sort(arr, size);

    EXPECT_EQ(size, 0);
}