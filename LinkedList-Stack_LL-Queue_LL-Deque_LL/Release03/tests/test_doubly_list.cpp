#include "gtest/gtest.h"
#include "Release02/List/headers/DoublyList.h"
#include <stdexcept>
#include <string>

// Test fixture for DoublyList
class DoublyListTest : public ::testing::Test {
protected:
    DoublyList<int> intList;
    DoublyList<std::string> stringList;
};

// Test pushFront and front
TEST_F(DoublyListTest, PushFront) {
    intList.pushFront(10);
    intList.pushFront(20);
    EXPECT_EQ(intList.front(), 20);
    EXPECT_EQ(intList.getSize(), 2);
}

// Test pushBack and back
TEST_F(DoublyListTest, PushBack) {
    intList.pushBack(30);
    intList.pushBack(40);
    EXPECT_EQ(intList.back(), 40);
    EXPECT_EQ(intList.getSize(), 2);
}

// Test popFront
TEST_F(DoublyListTest, PopFront) {
    intList.pushFront(10);
    intList.pushFront(20);
    intList.popFront();
    EXPECT_EQ(intList.front(), 10);
    EXPECT_EQ(intList.getSize(), 1);
}

// Test popBack
TEST_F(DoublyListTest, PopBack) {
    intList.pushBack(30);
    intList.pushBack(40);
    intList.popBack();
    EXPECT_EQ(intList.back(), 30);
    EXPECT_EQ(intList.getSize(), 1);
}

// Test insert
TEST_F(DoublyListTest, Insert) {
    intList.pushBack(10);
    intList.pushBack(30);
    intList.insert(1, 20);
    EXPECT_EQ(intList.front(), 10);
    EXPECT_EQ(intList.back(), 30);

    // Verify inserted value
        auto* curr = intList.front();
    EXPECT_EQ(curr, 10);
    curr = curr->next->data;
    EXPECT_EQ(curr, 20);
    curr = curr->next->data;
    EXPECT_EQ(curr, 30);
}

// Test erase
TEST_F(DoublyListTest, Erase) {
    intList.pushBack(10);
    intList.pushBack(20);
    intList.pushBack(30);
    intList.erase(1);
    EXPECT_EQ(intList.getSize(), 2);
    EXPECT_EQ(intList.front(), 10);
    EXPECT_EQ(intList.back(), 30);
}

// Test clear
TEST_F(DoublyListTest, Clear) {
    intList.pushBack(10);
    intList.pushBack(20);
    intList.clear();
    EXPECT_EQ(intList.getSize(), 0);
    EXPECT_TRUE(intList.isEmpty());
}

// Test isEmpty
TEST_F(DoublyListTest, IsEmpty) {
    EXPECT_TRUE(intList.isEmpty());
    intList.pushBack(10);
    EXPECT_FALSE(intList.isEmpty());
}

// Test exceptions for front and back
TEST_F(DoublyListTest, FrontBackExceptions) {
    EXPECT_THROW(intList.front(), std::runtime_error);
    EXPECT_THROW(intList.back(), std::runtime_error);
}

// Test process function with a lambda
TEST_F(DoublyListTest, Process) {
    intList.pushBack(1);
    intList.pushBack(2);
    intList.pushBack(3);

    int sum = 0;
    intList.process([&sum](int& data) { sum += data; });
    EXPECT_EQ(sum, 6);
}

// Test bidirectional traversal
TEST_F(DoublyListTest, BidirectionalTraversal) {
    intList.pushBack(1);
    intList.pushBack(2);
    intList.pushBack(3);

    // Verify forward traversal
    auto* curr = intList.front();
    EXPECT_EQ(curr->data, 1);
    curr = curr->next.get();
    EXPECT_EQ(curr->data, 2);
    curr = curr->next.get();
    EXPECT_EQ(curr->data, 3);

    // Verify backward traversal
    curr = intList.back();
    EXPECT_EQ(curr->data, 3);
    curr = curr->prev;
    EXPECT_EQ(curr->data, 2);
    curr = curr->prev;
    EXPECT_EQ(curr->data, 1);
}

// Test string specialization
TEST_F(DoublyListTest, StringList) {
    stringList.pushBack("Hello");
    stringList.pushBack("World");
    EXPECT_EQ(stringList.front(), "Hello");
    EXPECT_EQ(stringList.back(), "World");
    EXPECT_EQ(stringList.getSize(), 2);
}
