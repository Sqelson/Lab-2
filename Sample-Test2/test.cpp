#include "pch.h"

#include <chrono>
#include <gtest/gtest.h>
#include "../dictionary/dictionary.h"

// Define a helper function to check if a key is present in the dictionary. The test output is displayed here.
void isPresent(Dictionary& dict, int k, std::string i) {
    std::string* p_i = dict.lookupNode(k);  // Assuming the method name is lookupNode
    // If p_i is nullptr, the test will fail and print the message.
    ASSERT_NE(p_i, nullptr) << std::to_string(k) + " is missing"; // If p_i is nullptr, the test will fail and print the message.
    // If the values are not equal, the test will fail and print the message.
    EXPECT_EQ(*p_i, i) << std::to_string(k) + " should be " + i + ", but found " + *p_i; // If the values are not equal, the test will fail and print the message.
}

// Define a helper function to check if a key is absent from the dictionary. The test output is displayed here.
void isAbsent(Dictionary& dict, int k) {
    // If the values are not equal (i.e., dict.lookupNode(k) is not nullptr), 
    // the test will fail and print the message.
    EXPECT_EQ(dict.lookupNode(k), nullptr) << std::to_string(k) + " should be absent, but is present.";
}

// Define a helper function to insert test data into the dictionary.
void insertTestData(Dictionary& dict) {
    dict.insertNode(22, "Jane");
    dict.insertNode(22, "Mary");
    dict.insertNode(0, "Harold");
    dict.insertNode(9, "Edward");
    dict.insertNode(37, "Victoria");
    dict.insertNode(4, "Matilda");
    dict.insertNode(26, "Oliver");
    dict.insertNode(42, "Elizabeth");
    dict.insertNode(19, "Henry");
    dict.insertNode(4, "Stephen");
    dict.insertNode(24, "James");
    dict.insertNode(-1, "Edward");
    dict.insertNode(31, "Anne");
    dict.insertNode(23, "Elizabeth");
    dict.insertNode(1, "William");
    dict.insertNode(26, "Charles");
}

// Initial test cases that do not use the dictionary from the labs.

// Test case for inserting and looking up values in the Dictionary.
TEST(DictionaryTest, InsertAndLookup) {
    Dictionary dict;  // Create a Dictionary object

    // Test inserting a new key-value pair
    dict.insertNode(1, "one");
    std::string* value = dict.lookupNode(1);  // Look up the value using the key
    ASSERT_NE(value, nullptr);  // Ensure the returned pointer is not null
    EXPECT_EQ(*value, "one");  // Check if the returned value is correct

    // Repeat the above steps for different key-value pairs
    dict.insertNode(2, "two");
    value = dict.lookupNode(2);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(*value, "two");

    dict.insertNode(-1, "negative one");
    value = dict.lookupNode(-1);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(*value, "negative one");
}

// Test case for overwriting values of existing keys in the Dictionary.
TEST(DictionaryTest, OverwriteExistingKey) {
    Dictionary dict;

    // Insert a key-value pair and check its value
    dict.insertNode(1, "one");
    std::string* value = dict.lookupNode(1);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(*value, "one");

    // Overwrite the value of the existing key and check the new value
    dict.insertNode(1, "uno");
    value = dict.lookupNode(1);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(*value, "uno");
}

// Test case for looking up keys that do not exist in the Dictionary.
TEST(DictionaryTest, LookupNonexistentKey) {
    Dictionary dict;

    // Attempt to look up a key that hasn't been inserted, expecting a null pointer
    std::string* value = dict.lookupNode(1);
    EXPECT_EQ(value, nullptr);
}

// Test case for inserting multiple key-value pairs and looking them up in the Dictionary.
TEST(DictionaryTest, InsertMultipleAndLookup) {
    Dictionary dict;

    // Insert multiple key-value pairs
    dict.insertNode(1, "one");
    dict.insertNode(2, "two");
    dict.insertNode(3, "three");

    // Look up each key and check the values
    std::string* value = dict.lookupNode(1);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(*value, "one");

    value = dict.lookupNode(2);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(*value, "two");

    value = dict.lookupNode(3);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(*value, "three");
}

// Test case for inserting and looking up values when the Dictionary is initially empty.
TEST(DictionaryTest, InsertAndLookupWhenEmpty) {
    Dictionary dict;

    // Insert a key-value pair and check its value
    dict.insertNode(1, "one");
    std::string* value = dict.lookupNode(1);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(*value, "one");
}

// Test case for inserting and looking up a large number of key-value pairs.
TEST(DictionaryTest, InsertAndLookupLargeNumber) {
    Dictionary dict;

    // Insert a large number of key-value pairs
    for (int i = 0; i < 1000; ++i) {
        dict.insertNode(i, std::to_string(i));
    }

    // Look up each key and check the values
    for (int i = 0; i < 1000; ++i) {
        std::string* value = dict.lookupNode(i);
        ASSERT_NE(value, nullptr);
        EXPECT_EQ(*value, std::to_string(i));
    }
}

// Test case for measuring the performance of insertion and lookup operations.
TEST(DictionaryTest, PerformanceTest) {
    Dictionary dict;

    // Measure the time taken to insert a large number of key-value pairs
    auto start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        dict.insertNode(i, std::to_string(i));
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "Time taken to insert 1000 key-value pairs: " << duration.count() << " ms" << std::endl;

    // Measure the time taken to look up a large number of keys
    start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        dict.lookupNode(i);
    }
    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "Time taken to look up 1000 keys: " << duration.count() << " ms" << std::endl;
}

// Additional tests using the dictionary from the labs.

// Test removing the root node when it only has a left child.
TEST(DictionaryTest, RemoveRootWithLeftChild) {
    Dictionary dict;  // Create a new Dictionary instance.
    dict.insertNode(31, "Anne");  // Insert a root node.
    dict.insertNode(7, "John");  // Insert a left child.
    dict.removeNode(31);  // Remove the root node.

    isAbsent(dict, 31);  // Check root node is removed.
    isPresent(dict, 7, "John");  // Check left child node is present and correct.
}

// Test removing the root node when it only has a right child.
TEST(DictionaryTest, RemoveRootWithRightChild) {
    Dictionary dict;  // Create a new Dictionary instance.
    dict.insertNode(7, "John");  // Insert a root node.
    dict.insertNode(31, "Anne");  // Insert a right child.
    dict.removeNode(31);  // Remove the right child node.

    isAbsent(dict, 31);  // Check right child node is removed.
    isPresent(dict, 7, "John");  // Check root node is present and correct.
}

// Test inserting many nodes, then removing nodes that only have one child.
TEST(DictionaryTest, InsertMany_RemoveNodesWithOneChild) {
    Dictionary dict;  // Create a new Dictionary instance.
    insertTestData(dict);  // Insert test data.

    dict.removeNode(4);  // Remove a node with one child.
    isAbsent(dict, 4);  // Check node is removed.

    dict.removeNode(1);  // Remove another node with one child.
    isAbsent(dict, 1);  // Check node is removed.

    dict.removeNode(9);  // Remove another node with one child.
    isAbsent(dict, 9);  // Check node is removed.

    // Verify other nodes are still present and unaffected.
    isPresent(dict, 22, "Mary");
    isPresent(dict, 0, "Harold");
    isPresent(dict, 24, "James");
    // ... other checks ...
}

// Test removing the root node when it has both left and right children.
TEST(DictionaryTest, RemoveRootWithChildren) {
    Dictionary dict;  // Create a new Dictionary instance.
    dict.insertNode(31, "Anne");  // Insert a root node.
    dict.insertNode(7, "John");  // Insert a left child.
    dict.insertNode(42, "Elizabeth");  // Insert a right child.
    dict.removeNode(31);  // Remove the root node.

    isAbsent(dict, 31);  // Check root node is removed.
    isPresent(dict, 7, "John");  // Check left child node is present and correct.
    isPresent(dict, 42, "Elizabeth");  // Check right child node is present and correct.
}

// Test inserting many nodes, then removing nodes that have two children.
TEST(DictionaryTest, InsertMany_RemoveNodesWithChildren) {
    Dictionary dict;  // Create a new Dictionary instance.
    insertTestData(dict);  // Insert test data.

    dict.removeNode(0);  // Remove a node with two children.
    isAbsent(dict, 0);  // Check node is removed.

    dict.removeNode(37);  // Remove another node with two children.
    isAbsent(dict, 37);  // Check node is removed.

    dict.removeNode(22);  // Remove another node with two children.
    isAbsent(dict, 22);  // Check node is removed.

    // Verify other nodes are still present and unaffected.
    isPresent(dict, 4, "Stephen");
    isPresent(dict, 9, "Edward");
    isPresent(dict, 1, "William");
    // ... other checks ...
}

// Test inserting many nodes, then attempting to remove a node that doesn't exist.
TEST(DictionaryTest, InsertMany_RemoveAbsent) {
    Dictionary dict;  // Create a new Dictionary instance.
    insertTestData(dict);  // Insert test data.

    dict.removeNode(6);  // Attempt to remove a node that doesn't exist.
    isAbsent(dict, 6);  // Check node is still absent.

    // Verify other nodes are still present and unaffected.
    isPresent(dict, 22, "Mary");
    isPresent(dict, 4, "Stephen");
    isPresent(dict, 9, "Edward");
    // ... other checks ...
}

// Test case for the destructor and deepDeleteWorker function
TEST(DictionaryTest, DestructorAndDeepDelete) {
    Dictionary* dict = new Dictionary;

    // Insert multiple key-value pairs
    // -> is used because dict is a pointer. If dict was not a pointer, you would use the . operator instead.
    // This is also why we do not use the insertTestData function here, because it takes a Dictionary object, not a pointer.
    dict->insertNode(1, "one");
    dict->insertNode(2, "two");
    dict->insertNode(3, "three");

    // Call the destructor by deleting the Dictionary object
    delete dict;

    // After deleting the Dictionary object, attempt to access it (which should crash if memory is not properly de-allocated)
    // If the program reaches this point without crashing, it suggests that the memory was successfully de-allocated
    EXPECT_ANY_THROW({
        dict->insertNode(10, "ten");
		// This test currently fails, for reasons that are not clear to me
        });
}