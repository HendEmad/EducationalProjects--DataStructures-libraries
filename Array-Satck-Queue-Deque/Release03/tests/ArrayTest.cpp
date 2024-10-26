#include "gtest/gtest.h"
#include "Array.h"

TEST(ArrayTest, AddElement) {
    Array array(2);
    array.add_element(10);
    array.add_element(20);
    
    EXPECT_EQ(array.get_size(), 2);
    EXPECT_EQ(array.get_element(0), 10);
    EXPECT_EQ(array.get_element(1), 20);
}

TEST(ArrayTest, ResizeArray) {
    Array array(2);
    array.add_element(10);
    array.add_element(20);
    array.add_element(30); // This should trigger resize
    
    EXPECT_EQ(array.get_size(), 3);
    EXPECT_EQ(array.get_element(2), 30);
    EXPECT_EQ(array.get_capacity(), 4); // Capacity should have doubled
}

TEST(ArrayTest, RemoveElement) {
    Array array(2);
    array.add_element(10);
    array.add_element(20);
    
    int removed_element = array.remove_element();
    EXPECT_EQ(removed_element, 20);
    EXPECT_EQ(array.get_size(), 1);
    
    removed_element = array.remove_element();
    EXPECT_EQ(removed_element, 10);
    EXPECT_EQ(array.get_size(), 0);
}

TEST(ArrayTest, SearchElement) {
    Array array(2);
    array.add_element(10);
    array.add_element(20);
    
    array.search(20); // Should print element found at index 1
    array.search(30); // Should print element not found
}

TEST(ArrayTest, begin) {
    Array array(3);
    array.add_element(10);
    array.add_element(20);
    array.add_element(30);

    int* ptr = array.begin();
    EXPECT_EQ(ptr, array.get_element(0));
    EXPECT_EQ(*ptr, 10);

    EXPECT_EQ(array.get_size(), 3);
    EXPECT_EQ(array.get_element(1), 20);
    EXPECT_EQ(array.get_element(2), 30);
}

TEST(ArrayTest, CBegin) {
    Array array(3);
    array.add_element(10);
    array.add_element(20);
    array.add_element(30);

    const int* ptr = array.cbegin();
    ASSERT_NE(ptr, nullptr);  // check that the pointer is exist (not nullptr)
    EXPECT_EQ(*ptr, 10);      
    EXPECT_EQ(*(ptr + 1), 20);
    EXPECT_EQ(*(ptr + 2), 30); 
}

TEST(ArrayTest, End) {
    Array array(3);
    array.add_element(10);
    array.add_element(20);
    array.add_element(30);

    int* ptr = array.end();
    ASSERT_NE(ptr, nullptr);  
    EXPECT_EQ(*(ptr - 1), 30); 
}

TEST(ArrayTest, CEnd) {
    Array array(3);
    array.add_element(10);
    array.add_element(20);
    array.add_element(30);

    const int* ptr = array.cend();
    ASSERT_NE(ptr, nullptr);  
    EXPECT_EQ(*(ptr - 1), 30); 
}