#include <gtest/gtest.h>
#include "vector.hpp"
#include <string>

using vitashaa::Vector;

TEST(VectorTest, DefaultConstructor) {
    Vector<int> v;
}

TEST(VectorTest, PushBackAndSize) {
    Vector<std::string> v;
    v.push_back("first");
    v.push_back("second");

    EXPECT_EQ(v.get_size(), 2);
    EXPECT_TRUE(v.has_item("first"));
    EXPECT_TRUE(v.has_item("second"));
}

TEST(VectorTest, HasItemWithDifferentTypes) {
    Vector<double> v;
    v.push_back(3.14);
    v.push_back(2.71);

    EXPECT_TRUE(v.has_item(3.14));
    EXPECT_FALSE(v.has_item(1.41));
}

TEST(VectorTest, InsertAtDifferentPositions) {
    Vector<char> v;
    v.push_back('a');
    v.push_back('c');

    EXPECT_TRUE(v.insert(1, 'b'));
    EXPECT_EQ(v.get_size(), 3);

    EXPECT_TRUE(v.insert(0, 'x'));
    EXPECT_EQ(v.get_size(), 4);

    EXPECT_TRUE(v.insert(4, 'd'));
    EXPECT_EQ(v.get_size(), 5);

    EXPECT_FALSE(v.insert(10, 'z'));
}

TEST(VectorTest, CapacityIncrease) {
    Vector<int> v;
    const int test_size = 20;

    for (int i = 0; i < test_size; ++i) {
        v.push_back(i);
    }

    EXPECT_EQ(v.get_size(), test_size);
    for (int i = 0; i < test_size; ++i) {
        EXPECT_TRUE(v.has_item(i));
    }
}

TEST(VectorTest, RemoveFirstOccurrence) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(20);

    EXPECT_TRUE(v.remove_first(20));
    EXPECT_EQ(v.get_size(), 3);
    EXPECT_TRUE(v.has_item(20));

    EXPECT_FALSE(v.remove_first(99));
    EXPECT_EQ(v.get_size(), 3);
}

TEST(VectorTest, PrintOutput) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    std::cout << "will be: [1, 2, 3]: ";
    v.print();
}

TEST(VectorTest, MemoryManagement) {
    Vector<std::string>* v = new Vector<std::string>();
    v->push_back("test");
    v->push_back("memory");
    delete v;
}

TEST(VectorTest, EdgeCases) {
    Vector<int> v;

    EXPECT_TRUE(v.insert(0, 100));

    EXPECT_TRUE(v.remove_first(100));
    EXPECT_EQ(v.get_size(), 0);

    EXPECT_FALSE(v.remove_first(100));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}