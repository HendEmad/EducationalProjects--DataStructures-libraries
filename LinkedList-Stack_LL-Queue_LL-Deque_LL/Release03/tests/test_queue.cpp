#include "gtest/gtest.h"
#include "Release03/LinearDS/headers/Queue.h"
#include "Release03/List/headers/ForwardList.h"
#include "Release03/List/headers/DoublyList.h"
#include "Release03/List/headers/CircularList.h"

// Define a fixture class for parameterized testing
template <typename ListType>
class QueueTest : public ::testing::Test {
protected:
    IList<int>* list;
    Queue<int>* queue;

    void SetUp() override {
        list = new ListType();  
        queue = new Queue<int>(list);
    }

    void TearDown() override {
        delete queue;
        delete list;
    }
};

// Instantiate the fixture with all list types
using ListTypes = ::testing::Types<ForwardList<int>, DoublyList<int>, CircularList<int>>;
TYPED_TEST_SUITE(QueueTest, ListTypes);

// Test that a new queue is initially empty
TYPED_TEST(QueueTest, QueueIsInitiallyEmpty) {
    EXPECT_TRUE(this->queue->empty());
}

// Test enqueue and dequeue operations
TYPED_TEST(QueueTest, EnqueueAndDequeue) {
    this->queue->enqueue(10);
    this->queue->enqueue(20);
    this->queue->enqueue(30);

    EXPECT_EQ(this->queue->front(), 10); 
    this->queue->dequeue();
    EXPECT_EQ(this->queue->front(), 20); 

    this->queue->dequeue();
    EXPECT_EQ(this->queue->front(), 30); 

    this->queue->dequeue();
    EXPECT_TRUE(this->queue->empty()); 
}

// Test clearing the queue
TYPED_TEST(QueueTest, ClearQueue) {
    this->queue->enqueue(5);
    this->queue->enqueue(15);
    this->queue->enqueue(25);

    this->queue->clear();
    EXPECT_TRUE(this->queue->empty());
}

// Test queue front on empty queue (exception expected)
TYPED_TEST(QueueTest, FrontThrowsOnEmpty) {
    EXPECT_THROW(this->queue->front(), std::runtime_error);
}

// Test queue operations with multiple elements
TYPED_TEST(QueueTest, EnqueueMultipleAndCheckOrder) {
    this->queue->enqueue(1);
    this->queue->enqueue(2);
    this->queue->enqueue(3);
    EXPECT_FALSE(this->queue->empty());

    EXPECT_EQ(this->queue->front(), 1);
    this->queue->dequeue();

    EXPECT_EQ(this->queue->front(), 2);
    this->queue->dequeue();

    EXPECT_EQ(this->queue->front(), 3);
    this->queue->dequeue();

    EXPECT_TRUE(this->queue->empty());
}
