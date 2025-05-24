#include "linked_list.hpp"
#include <iostream>

namespace vitashaa {

template<typename T>
LinkedList<T>::~LinkedList() {
    Node* current = begin;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

template<typename T>
std::size_t LinkedList<T>::get_size() const noexcept {
    return size;
}

template<typename T>
bool LinkedList<T>::has_item(const T& value) const noexcept {
    Node* current = begin;
    while (current != nullptr) {
        if (current->value == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

template<typename T>
void LinkedList<T>::print() const noexcept {
    Node* current = begin;
    std::cout << "[";
    while (current != nullptr) {
        std::cout << current->value;
        if (current->next != nullptr) {
            std::cout << " <-> ";
        }
        current = current->next;
    }
    std::cout << "]" << std::endl;
}

template<typename T>
void LinkedList<T>::push_back(const T& value) {
    Node* newNode = new Node(value);
    if (end != nullptr) {
        end->next = newNode;
        newNode->prev = end;
    } else {
        begin = newNode;
    }
    end = newNode;
    ++size;
}

template<typename T>
bool LinkedList<T>::remove_first(const T& value) noexcept {
    Node* current = begin;
    while (current != nullptr) {
        if (current->value == value) {
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                begin = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            } else {
                end = current->prev;
            }
            delete current;
            --size;
            return true;
        }
        current = current->next;
    }
    return false;
}

}