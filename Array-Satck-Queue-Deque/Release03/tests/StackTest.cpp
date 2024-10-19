#include "gtest/gtest.h"
#include "Stack.h"

TEST(StackTest, AddElement) {
    Stack stack(2);
    stack.add_element(10);
    stack.add_element(20);
    
    EXPECT_EQ(stack.peek(), 20);
}

TEST(StackTest, RemoveElement) {
    Stack stack(2);
    stack.add_element(10);
    stack.add_element(20);
    
    int removed = stack.remove_element();
    EXPECT_EQ(removed, 20);
    EXPECT_EQ(stack.peek(), 10);
}

TEST(StackTest, Peek) {
    Stack stack(2);
    stack.add_element(10);
    stack.add_element(20);
    
    EXPECT_EQ(stack.peek(), 20);
}

TEST(StackTest, SearchElement) {
    Stack stack(2);
    stack.add_element(10);
    stack.add_element(20);
    
    stack.search(20);  // Should find element at the top
    stack.search(30);  // Should print element not found
}

TEST(StackTest, ProcessElements) {
    Stack stack(2);
    stack.add_element(10);
    stack.add_element(20);
    
    int sum = 0;
    stack.process_elements([&sum](int element) {
        sum += element;
    });
    
    EXPECT_EQ(sum, 30);  // 10 + 20 = 30
}
