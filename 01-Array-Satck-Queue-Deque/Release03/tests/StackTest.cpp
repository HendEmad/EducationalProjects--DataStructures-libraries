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

TEST(StackTests, EmplaceFunction) {
    Stack stack;  

    stack.emplace(1);  
    EXPECT_EQ(stack.peek(), 1); 

    stack.emplace(2);
    EXPECT_EQ(stack.peek(), 2); 

    stack.emplace(3);
    EXPECT_EQ(stack.peek(), 3);

    EXPECT_EQ(stack.array.get_size(), 3); 
}

TEST(StackTests, SwapFunction) {
    Stack stack1; 
    Stack stack2; 

    stack1.add_element(1);
    stack1.add_element(2);

    stack2.add_element(3);
    stack2.add_element(4);

    EXPECT_EQ(stack1.peek(), 2);
    EXPECT_EQ(stack2.peek(), 4); 

    stack1.swap(stack2);

    EXPECT_EQ(stack1.peek(), 4); 
    EXPECT_EQ(stack2.peek(), 2); 

    EXPECT_EQ(stack1.array.get_size(), 2);
    EXPECT_EQ(stack2.array.get_size(), 2);
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
