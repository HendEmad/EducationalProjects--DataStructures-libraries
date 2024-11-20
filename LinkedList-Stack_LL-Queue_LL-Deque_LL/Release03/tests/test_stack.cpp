#include "gtest/gtest.h"
#include "Release03/LinearDS/headers/Stack.h"
#include "Release03/List/headers/ForwardList.h"
#include "Release03/List/headers/DoublyList.h"
#include "Release03/List/headers/CircularList.h"

// Define a fixture class for parameterized testing
template <typename ListType>
class StackTest : public ::testing::Test {
protected:
    IList<int>* list;
    Stack<int>* stack;

    void SetUp() override {
        list = new ListType();   // Create the appropriate list type
        stack = new Stack<int>(list);
    }

    void TearDown() override {
        delete stack;
        delete list;
    }
};

// Instantiate the fixture with all list types
using ListTypes = ::testing::Types<ForwardList<int>, DoublyList<int>, CircularList<int>>;
TYPED_TEST_SUITE(StackTest, ListTypes);

// Test that a new stack is initially empty
TYPED_TEST(StackTest, StackIsInitiallyEmpty) {
    EXPECT_TRUE(this->stack->empty());
    EXPECT_EQ(this->stack->empty(), true);
}

// Test pushing and popping elements
TYPED_TEST(StackTest, PushAndPop) {
    this->stack->push(10);
    this->stack->push(20);
    this->stack->push(30);

    EXPECT_EQ(this->stack->top(), 30);
    this->stack->pop();
    EXPECT_EQ(this->stack->top(), 20);
    this->stack->pop();
    EXPECT_EQ(this->stack->top(), 10);
    this->stack->pop();
    EXPECT_TRUE(this->stack->empty());
}

// Test clearing the stack
TYPED_TEST(StackTest, ClearStack) {
    this->stack->push(5);
    this->stack->push(15);
    this->stack->push(25);

    this->stack->clear();
    EXPECT_TRUE(this->stack->empty());
}

// Test stack top on empty stack (exception expected)
TYPED_TEST(StackTest, TopThrowsOnEmpty) {
    EXPECT_THROW(this->stack->top(), std::runtime_error);
}

// Test stack operations with multiple elements
TYPED_TEST(StackTest, PushMultipleAndCheckSize) {
    this->stack->push(1);
    this->stack->push(2);
    this->stack->push(3);
    EXPECT_FALSE(this->stack->empty());

    EXPECT_EQ(this->stack->top(), 3);
    this->stack->pop();

    EXPECT_EQ(this->stack->top(), 2);
    this->stack->pop();

    EXPECT_EQ(this->stack->top(), 1);
    this->stack->pop();

    EXPECT_TRUE(this->stack->empty());
}