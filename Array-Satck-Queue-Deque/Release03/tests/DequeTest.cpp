#include "gtest/gtest.h"
#include "Deque.h"

TEST(DequeTest, AddElementFront) {
    Deque deque(2);
    deque.add_element(10, deque_operations::FRONT);
    deque.add_element(20, deque_operations::FRONT);
    
    EXPECT_EQ(deque.get_front(), 20);
}

TEST(DequeTest, AddElementRear) {
    Deque deque(2);
    deque.add_element(10, deque_operations::REAR);
    deque.add_element(20, deque_operations::REAR);
    
    EXPECT_EQ(deque.get_rear(), 20);
}

TEST(DequeTest, RemoveElementFront) {
    Deque deque(2);
    deque.add_element(10, deque_operations::FRONT);
    deque.add_element(20, deque_operations::FRONT);
    
    int removed = deque.remove_element(deque_operations::FRONT);
    EXPECT_EQ(removed, 20);
    EXPECT_EQ(deque.get_front(), 10);
}

TEST(DequeTest, RemoveElementRear) {
    Deque deque(2);
    deque.add_element(10, deque_operations::REAR);
    deque.add_element(20, deque_operations::REAR);
    
    int removed = deque.remove_element(deque_operations::REAR);
    EXPECT_EQ(removed, 20);
    EXPECT_EQ(deque.get_rear(), 10);
}

TEST(DequeTest, SearchElement) {
    Deque deque(2);
    deque.add_element(10, deque_operations::FRONT);
    deque.add_element(20, deque_operations::REAR);
    
    deque.search(20, deque.get_front_idx()); // Should find element at rear
    deque.search(30, deque.get_front_idx()); // Should print element not found
}

TEST(DequeTest, ProcessElements) {
    Deque deque(2);
    deque.add_element(10, deque_operations::FRONT);
    deque.add_element(20, deque_operations::REAR);
    
    int sum = 0;
    deque.process_elements([&sum](int element) {
        sum += element;
    });
    
    EXPECT_EQ(sum, 30);  // 10 + 20 = 30
}
