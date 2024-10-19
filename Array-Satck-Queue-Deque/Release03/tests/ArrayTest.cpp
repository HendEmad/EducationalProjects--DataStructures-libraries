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
