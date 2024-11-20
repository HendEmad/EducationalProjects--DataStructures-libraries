#include "gtest/gtest.h"
#include "Release03/List/headers/CircularList.h"
#include <stdexcept>
#include <string>

// Test fixture for CircularList
class CircularListTest : public ::testing::Test {
protected:
    CircularList<int> intList;
    CircularList<std::string> stringList;
};

// Test pushFront and front
TEST_F(CircularListTest, PushFront) {
    intList.pushFront(10);
    intList.pushFront(20);
    EXPECT_EQ(intList.front(), 20);
    EXPECT_EQ(intList.getSize(), 2);
}

// Test pushBack and back
TEST_F(CircularListTest, PushBack) {
    intList.pushBack(30);
    intList.pushBack(40);
    EXPECT_EQ(intList.back(), 40);
    EXPECT_EQ(intList.getSize(), 2);
}

// Test popFront
TEST_F(CircularListTest, PopFront) {
    intList.pushFront(10);
    intList.pushFront(20);
    intList.popFront();
    EXPECT_EQ(intList.front(), 10);
    EXPECT_EQ(intList.getSize(), 1);
}

// Test popBack
TEST_F(CircularListTest, PopBack) {
    intList.pushBack(30);
    intList.pushBack(40);
    intList.popBack();
    EXPECT_EQ(intList.back(), 30);
    EXPECT_EQ(intList.getSize(), 1);
}

// Test insert
TEST_F(CircularListTest, Insert) {
    intList.pushBack(10);
    intList.pushBack(30);
    intList.insert(1, 20);
    EXPECT_EQ(intList.front(), 10);
    EXPECT_EQ(intList.back(), 30);

    // Verify inserted value
    intList.popFront(); // Removes 10
    EXPECT_EQ(intList.front(), 20);
}

// Test erase
TEST_F(CircularListTest, Erase) {
    intList.pushBack(10);
    intList.pushBack(20);
    intList.pushBack(30);
    intList.erase(1);
    EXPECT_EQ(intList.getSize(), 2);
    EXPECT_EQ(intList.front(), 10);
    EXPECT_EQ(intList.back(), 30);
}

// Test clear
TEST_F(CircularListTest, Clear) {
    intList.pushBack(10);
    intList.pushBack(20);
    intList.clear();
    EXPECT_EQ(intList.getSize(), 0);
    EXPECT_TRUE(intList.isEmpty());
}

// Test isEmpty
TEST_F(CircularListTest, IsEmpty) {
    EXPECT_TRUE(intList.isEmpty());
    intList.pushBack(10);
    EXPECT_FALSE(intList.isEmpty());
}

// Test exceptions for front and back
TEST_F(CircularListTest, FrontBackExceptions) {
    EXPECT_THROW(intList.front(), std::runtime_error);
    EXPECT_THROW(intList.back(), std::runtime_error);
}

// Test circular nature
TEST_F(CircularListTest, Circularity) {
    intList.pushBack(1);
    intList.pushBack(2);
    intList.pushBack(3);

    EXPECT_EQ(intList.back(), 3);

    // Verify the circular link
    EXPECT_EQ(intList.back()->next->data, 1);
}

// Test process function with a lambda
TEST_F(CircularListTest, Process) {
    intList.pushBack(1);
    intList.pushBack(2);
    intList.pushBack(3);

    int sum = 0;
    intList.process([&sum](int& data) { sum += data; });
    EXPECT_EQ(sum, 6);
}

// Test string specialization
TEST_F(CircularListTest, StringList) {
    stringList.pushBack("Hello");
    stringList.pushBack("World");
    EXPECT_EQ(stringList.front(), "Hello");
    EXPECT_EQ(stringList.back(), "World");
    EXPECT_EQ(stringList.getSize(), 2);
}
