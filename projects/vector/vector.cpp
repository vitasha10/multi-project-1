#include "vector.hpp"
#include <iostream>

namespace vitashaa {

template <typename T>
const std::size_t Vector<T>::START_CAPACITY = 10;

template<typename T>
Vector<T>::Vector() : size(0), capacity(START_CAPACITY) {
    arr = new T[capacity];
}

template<typename T>
Vector<T>::~Vector() {
    delete[] arr;
}

template<typename T>
std::size_t Vector<T>::get_size() const noexcept {
    return size;
}

template<typename T>
bool Vector<T>::has_item(const T& value) const noexcept {
    for (std::size_t i = 0; i < size; ++i) {
        if (arr[i] == value) {
            return true;
        }
    }
    return false;
}

template<typename T>
bool Vector<T>::insert(const std::size_t position, const T& value) {
    if (position > size) {
        return false;
    }

    if (size == capacity) {
        std::size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
        T* new_data = new T[new_capacity];

        for (std::size_t i = 0; i < position; ++i) {
            new_data[i] = arr[i];
        }

        new_data[position] = value;
        for (std::size_t i = position; i < size; ++i) {
            new_data[i + 1] = arr[i];
        }

        delete[] arr;
        arr = new_data;
        capacity = new_capacity;
    } else {
        for (std::size_t i = size; i > position; --i) {
            arr[i] = arr[i - 1];
        }
        arr[position] = value;
    }

    ++size;
    return true;
}

template<typename T>
void Vector<T>::print() const noexcept {
    std::cout << "[";
    for (std::size_t i = 0; i < size; ++i) {
        std::cout << arr[i];
        if (i != size - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

template<typename T>
void Vector<T>::push_back(const T& value) {
    if (size == capacity) {
        std::size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
        T* new_data = new T[new_capacity];

        for (std::size_t i = 0; i < size; ++i) {
            new_data[i] = arr[i];
        }

        delete[] arr;
        arr = new_data;
        capacity = new_capacity;
    }

    arr[size] = value;
    ++size;
}

template<typename T>
bool Vector<T>::remove_first(const T& value) {
    for (std::size_t i = 0; i < size; ++i) {
        if (arr[i] == value) {
            for (std::size_t j = i; j < size - 1; ++j) {
                arr[j] = arr[j + 1];
            }
            --size;
            return true;
        }
    }
    return false;
}

}