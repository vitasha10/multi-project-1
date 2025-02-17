#include <iostream>
#include "bubble_sort.hpp"

// Реализация функции сортировки
void bubble_sort(int* const arr, const int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int x = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = x;
            }
        }
    }
}

// Реализация функции для печати массива
void print_array(const char* const comment, int* arr, const int size) {
    const char format = ' ';
    std::cout << comment;
    for (int i = 0; i < size; i++) {
        std::cout << format << arr[i];
    }
    std::cout << std::endl;
}