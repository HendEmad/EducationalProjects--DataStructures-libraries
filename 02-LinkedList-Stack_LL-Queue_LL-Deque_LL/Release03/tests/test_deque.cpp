#include "gtest/gtest.h"
#include "Release03/LinearDS/headers/Deque.h"
#include "Release03/List/headers/ForwardList.h"
#include "Release03/List/headers/DoublyList.h"
#include "Release03/List/headers/CircularList.h"

// Define a fixture class for parameterized testing
template <typename ListType>
class DequeTest : public ::testing::Test {
protected:
    IList<int>* list;
    Deque<int>* deque;

    void SetUp() override {
        list = new ListType();   
        deque = new Deque<int>(list);
    }

    void TearDown() override {
        delete deque;
        delete list;
    }
};

// Instantiate the fixture with all list types
using ListTypes = ::testing::Types<ForwardList<int>, DoublyList<int>, CircularList<int>>;
TYPED_TEST_SUITE(DequeTest, ListTypes);

// Test that a new deque is initially empty
TYPED_TEST(DequeTest, DequeIsInitiallyEmpty) {
    EXPECT_TRUE(this->deque->empty());
}

// Test push_front and push_back operations
TYPED_TEST(DequeTest, PushFrontAndPushBack) {
    this->deque->push_front(10);
    this->deque->push_back(20);
    this->deque->push_back(30);
    this->deque->push_front(5);

    EXPECT_EQ(this->deque->front(), 5);
    EXPECT_EQ(this->deque->back(), 30);
}

// Test pop_front and pop_back operations
TYPED_TEST(DequeTest, PopFrontAndPopBack) {
    this->deque->push_front(10);
    this->deque->push_back(20);
    this->deque->push_back(30);
    this->deque->push_front(5);

    this->deque->pop_front();
    EXPECT_EQ(this->deque->front(), 10);

    this->deque->pop_back();
    EXPECT_EQ(this->deque->back(), 20);
}

// Test clearing the deque
TYPED_TEST(DequeTest, ClearDeque) {
    this->deque->push_front(1);
    this->deque->push_back(2);
    this->deque->push_front(3);
    this->deque->push_back(4);

    this->deque->clear();
    EXPECT_TRUE(this->deque->empty());
}

// Test accessing front and back on an empty deque (exception expected)
TYPED_TEST(DequeTest, FrontAndBackThrowsOnEmpty) {
    EXPECT_THROW(this->deque->front(), std::runtime_error);
    EXPECT_THROW(this->deque->back(), std::runtime_error);
}

// Test deque with multiple operations
TYPED_TEST(DequeTest, MultipleOperations) {
    this->deque->push_back(1);
    this->deque->push_front(0);
    this->deque->push_back(2);
    this->deque->push_front(-1);

    EXPECT_EQ(this->deque->front(), -1);
    EXPECT_EQ(this->deque->back(), 2);

    this->deque->pop_front();
    EXPECT_EQ(this->deque->front(), 0);

    this->deque->pop_back();
    EXPECT_EQ(this->deque->back(), 1);
}
