#include "gtest/gtest.h"
#include "Queue.h"

TEST(QueueTest, AddElement) {
    Queue queue(2);
    queue.add_element(10);
    queue.add_element(20);
    
    EXPECT_EQ(queue.get_front(), 10);
}

TEST(QueueTest, RemoveElement) {
    Queue queue(2);
    queue.add_element(10);
    queue.add_element(20);
    
    int removed = queue.remove_element();
    EXPECT_EQ(removed, 10);
    EXPECT_EQ(queue.get_front(), 20);
}

TEST(QueueTest, GetFront) {
    Queue queue(2);
    queue.add_element(10);
    queue.add_element(20);
    
    EXPECT_EQ(queue.get_front(), 10);
}

TEST(QueueTest, SearchElement) {
    Queue queue(2);
    queue.add_element(10);
    queue.add_element(20);
    
    queue.search(20, queue.get_front_idx()); // Should find element
    queue.search(30, queue.get_front_idx()); // Should print element not found
}

TEST(QueueTest, ProcessElements) {
    Queue queue(2);
    queue.add_element(10);
    queue.add_element(20);
    
    int sum = 0;
    queue.process_elements([&sum](int element) {
        sum += element;
    });
    
    EXPECT_EQ(sum, 30);  // 10 + 20 = 30
}
