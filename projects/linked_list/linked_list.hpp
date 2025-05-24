#pragma once

#include <cstddef>

namespace vitashaa {
    template <typename T>
    class LinkedList {
    private:
        class Node {
        public:
            T value;
            Node* prev = nullptr;
            Node* next = nullptr;

            Node(const T& value) : value(value) {}
            Node(const Node&) = delete;
            Node& operator=(const Node&) = delete;
        };

        Node* begin = nullptr;
        Node* end = nullptr;
        std::size_t size = 0;

    public:
        LinkedList() noexcept = default;
        LinkedList(const LinkedList&) = delete;
        LinkedList& operator=(const LinkedList&) = delete;
        ~LinkedList();

        std::size_t get_size() const noexcept;
        bool has_item(const T& value) const noexcept;
        void print() const noexcept;
        void push_back(const T& value);
        bool remove_first(const T& value) noexcept;
    };
}