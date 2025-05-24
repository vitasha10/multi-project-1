#include <gtest/gtest.h>
#include "linked_list.hpp"
#include <string>

using vitashaa::LinkedList;

TEST(LinkedListTest, PushBackAndSize) {
    LinkedList<std::string> v;
    v.push_back("first");
    v.push_back("second");

    EXPECT_EQ(v.get_size(), 2);
    EXPECT_TRUE(v.has_item("first"));
    EXPECT_TRUE(v.has_item("second"));
}

TEST(LinkedListTest, HasItemWithDifferentTypes) {
    LinkedList<double> v;
    v.push_back(3.14);
    v.push_back(2.71);

    EXPECT_TRUE(v.has_item(3.14));
    EXPECT_FALSE(v.has_item(1.41));
}

TEST(LinkedListTest, RemoveFirst) {
    LinkedList<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    EXPECT_TRUE(v.remove_first(2));
    EXPECT_EQ(v.get_size(), 2);
    EXPECT_FALSE(v.has_item(2));
    EXPECT_FALSE(v.remove_first(42));
}

TEST(LinkedListTest, PrintOutput) {
    LinkedList<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    std::cout << "Will be: [1 <-> 2 <-> 3]: ";
    v.print();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}