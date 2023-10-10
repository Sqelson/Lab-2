#include "pch.h"

#include <chrono>
#include <gtest/gtest.h>
#include "../dictionary/dictionary.h"

// Test case for inserting and looking up values in the Dictionary.
TEST(DictionaryTest, InsertAndLookup) {
    Dictionary dict;  // Create a Dictionary object

    // Test inserting a new key-value pair
    dict.insert(1, "one");
    std::string* value = dict.lookup(1);  // Look up the value using the key
    ASSERT_NE(value, nullptr);  // Ensure the returned pointer is not null
    EXPECT_EQ(*value, "one");  // Check if the returned value is correct

    // Repeat the above steps for different key-value pairs
    dict.insert(2, "two");
    value = dict.lookup(2);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(*value, "two");

    dict.insert(-1, "negative one");
    value = dict.lookup(-1);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(*value, "negative one");
}

// Test case for overwriting values of existing keys in the Dictionary.
TEST(DictionaryTest, OverwriteExistingKey) {
    Dictionary dict;

    // Insert a key-value pair and check its value
    dict.insert(1, "one");
    std::string* value = dict.lookup(1);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(*value, "one");

    // Overwrite the value of the existing key and check the new value
    dict.insert(1, "uno");
    value = dict.lookup(1);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(*value, "uno");
}

// Test case for looking up keys that do not exist in the Dictionary.
TEST(DictionaryTest, LookupNonexistentKey) {
    Dictionary dict;

    // Attempt to look up a key that hasn't been inserted, expecting a null pointer
    std::string* value = dict.lookup(1);
    EXPECT_EQ(value, nullptr);
}

// Test case for inserting multiple key-value pairs and looking them up in the Dictionary.
TEST(DictionaryTest, InsertMultipleAndLookup) {
    Dictionary dict;

    // Insert multiple key-value pairs
    dict.insert(1, "one");
    dict.insert(2, "two");
    dict.insert(3, "three");

    // Look up each key and check the values
    std::string* value = dict.lookup(1);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(*value, "one");

    value = dict.lookup(2);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(*value, "two");

    value = dict.lookup(3);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(*value, "three");
}

// Additional tests

// Test case for inserting and looking up values when the Dictionary is initially empty.
TEST(DictionaryTest, InsertAndLookupWhenEmpty) {
    Dictionary dict;

    // Insert a key-value pair and check its value
    dict.insert(1, "one");
    std::string* value = dict.lookup(1);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(*value, "one");
}

// Test case for inserting and looking up a large number of key-value pairs.
TEST(DictionaryTest, InsertAndLookupLargeNumber) {
    Dictionary dict;

    // Insert a large number of key-value pairs
    for (int i = 0; i < 1000; ++i) {
        dict.insert(i, std::to_string(i));
    }

    // Look up each key and check the values
    for (int i = 0; i < 1000; ++i) {
        std::string* value = dict.lookup(i);
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
        dict.insert(i, std::to_string(i));
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "Time taken to insert 1000 key-value pairs: " << duration.count() << " ms" << std::endl;

    // Measure the time taken to look up a large number of keys
    start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        dict.lookup(i);
    }
    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "Time taken to look up 1000 keys: " << duration.count() << " ms" << std::endl;
}