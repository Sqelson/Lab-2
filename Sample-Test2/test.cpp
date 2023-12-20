#include <chrono>
#include "../dictionary/dictionary.h"
#include "gtest/gtest.h"

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

// Test case for looking up in an empty dictionary.
TEST(Lookup_InsertTests, EmptyLookup) {
    Dictionary dict;
    isAbsent(dict, 1);
}

// Test case for a single insertion.
TEST(Lookup_InsertTests, SingleInsert) {
    Dictionary dict;
    dict.insertNode(22, "Mary");
    // Optionally check if the insertion was successful.
}

// Test case for inserting a single element and then looking it up.
TEST(Lookup_InsertTests, SingleInsertLookup) {
    Dictionary dict;
    dict.insertNode(22, "Mary");
    isPresent(dict, 22, "Mary");
}

// Test case for overwriting an existing element and then looking it up.
TEST(Lookup_InsertTests, SingleOverwriteLookup) {
    Dictionary dict;
    dict.insertNode(22, "Jane");
    dict.insertNode(22, "Mary");
    isPresent(dict, 22, "Mary");
}

// Test case for multiple insertions.
TEST(Lookup_InsertTests, MultipleInsert) {
    Dictionary dict;
    insertTestData(dict);
}

// Test case for inserting multiple elements and then looking them up.
TEST(Lookup_InsertTests, MultipleInsertLookupPresent) {
    Dictionary dict;
    insertTestData(dict);

    isPresent(dict, 22, "Mary");
    isPresent(dict, 4, "Stephen");
    isPresent(dict, 9, "Edward");
    isPresent(dict, 1, "William");
    isPresent(dict, 0, "Harold");
    isPresent(dict, 24, "James");
    isPresent(dict, 26, "Charles");
    isPresent(dict, 19, "Henry");
    isPresent(dict, 31, "Anne");
    isPresent(dict, 23, "Elizabeth");
    isPresent(dict, 37, "Victoria");
    isPresent(dict, 42, "Elizabeth");
    isPresent(dict, -1, "Edward");
}

// Test case for inserting multiple elements and then checking for absent keys.
TEST(Lookup_InsertTests, MultipleInsertLookupAbsent) {
    Dictionary dict;
    insertTestData(dict);

    isAbsent(dict, 2);
    isAbsent(dict, 3);
    isAbsent(dict, -4);
    isAbsent(dict, 56);
    isAbsent(dict, 30);
}

// Test case for measuring the performance of insertion and lookup operations.
TEST(PerformanceTests, PerformanceTest) {
    Dictionary dict;

    // Measure the time taken to insert a large number of key-value pairs.
    auto start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        dict.insertNode(i, std::to_string(i));
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "Time taken to insert 1000 key-value pairs: " << duration.count() << " ms" << std::endl;

    // Measure the time taken to look up a large number of keys.
    start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        dict.lookupNode(i);
    }
    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "Time taken to look up 1000 keys: " << duration.count() << " ms" << std::endl;
}

// Test case for removing from an empty dictionary.
TEST(RemoveTests, EmptyRemove) {
    Dictionary dict;
    dict.removeNode(43);
    isAbsent(dict, 43);
}

// Test case for removing a childless root.
TEST(RemoveTests, RemoveChildlessRoot) {
    Dictionary dict;
    dict.insertNode(7, "John");
    dict.removeNode(7);
    isAbsent(dict, 7);
}

// Test case for removing the left child of the root.
TEST(RemoveTests, RemoveLeftChildOfRoot) {
    Dictionary dict;
    dict.insertNode(31, "Anne");
    dict.insertNode(7, "John");
    dict.removeNode(7);

    isAbsent(dict, 7);
    isPresent(dict, 31, "Anne");
}

// Test case for removing the right child of the root.
TEST(RemoveTests, RemoveRightChildOfRoot) {
    Dictionary dict;
    dict.insertNode(7, "John");
    dict.insertNode(31, "Anne");
    dict.removeNode(31);

    isAbsent(dict, 31);
    isPresent(dict, 7, "John");
}

// Test case for inserting many nodes and then removing childless nodes.
TEST(RemoveTests, InsertMany_RemoveChildlessNodes) {
    Dictionary dict;
    insertTestData(dict);

    dict.removeNode(-1);
    isAbsent(dict, -1);

    dict.removeNode(1);
    isAbsent(dict, 1);

    dict.removeNode(19);
    isAbsent(dict, 19);

    dict.removeNode(23);
    isAbsent(dict, 23);

    dict.removeNode(31);
    isAbsent(dict, 31);

    dict.removeNode(42);
    isAbsent(dict, 42);

    dict.removeNode(4);
    isAbsent(dict, 4);

    isPresent(dict, 22, "Mary");
    isPresent(dict, 9, "Edward");
    isPresent(dict, 0, "Harold");
    isPresent(dict, 24, "James");
    isPresent(dict, 26, "Charles");
    isPresent(dict, 37, "Victoria");
}

// Test case for overwriting and then removing.
TEST(RemoveTests, OverwriteThenRemove) {
    Dictionary dict;
    dict.insertNode(22, "Jane");
    dict.insertNode(22, "Mary");
    dict.insertNode(4, "Matilda");
    dict.insertNode(26, "Oliver");
    dict.insertNode(4, "Stephen");
    dict.insertNode(26, "Charles");

    dict.removeNode(4);
    isAbsent(dict, 4);

    dict.removeNode(26);
    isAbsent(dict, 26);

    dict.removeNode(22);
    isAbsent(dict, 22);
}

// Test case for removing the root with a left child.
TEST(RemoveTests, RemoveRootWithLeftChild) {
    Dictionary dict;
    dict.insertNode(31, "Anne");
    dict.insertNode(7, "John");
    dict.removeNode(31);

    isAbsent(dict, 31);
    isPresent(dict, 7, "John");
}

// Test case for removing the root with a right child.
TEST(RemoveTests, RemoveRootWithRightChild) {
    Dictionary dict;
    dict.insertNode(7, "John");
    dict.insertNode(31, "Anne");
    dict.removeNode(31);

    isAbsent(dict, 31);
    isPresent(dict, 7, "John");
}

// Test case for inserting many nodes and then removing nodes with one child.
TEST(RemoveTests, InsertMany_RemoveNodesWithOneChild) {
    Dictionary dict;
    insertTestData(dict);

    dict.removeNode(4);
    isAbsent(dict, 4);

    dict.removeNode(1);
    isAbsent(dict, 1);

    dict.removeNode(9);
    isAbsent(dict, 9);

    isPresent(dict, 22, "Mary");
    isPresent(dict, 0, "Harold");
    isPresent(dict, 24, "James");
    isPresent(dict, 26, "Charles");
    isPresent(dict, 19, "Henry");
    isPresent(dict, 31, "Anne");
    isPresent(dict, 23, "Elizabeth");
    isPresent(dict, 37, "Victoria");
    isPresent(dict, 42, "Elizabeth");
    isPresent(dict, -1, "Edward");
}

// Test case for removing the root with children.
TEST(RemoveTests, RemoveRootWithChildren) {
    Dictionary dict;
    dict.insertNode(31, "Anne");
    dict.insertNode(7, "John");
    dict.insertNode(42, "Elizabeth");
    dict.removeNode(31);

    isAbsent(dict, 31);
    isPresent(dict, 7, "John");
    isPresent(dict, 42, "Elizabeth");
}

// Test case for inserting many nodes and then removing nodes with children.
TEST(RemoveTests, InsertMany_RemoveNodesWithChildren) {
    Dictionary dict;
    insertTestData(dict);

    dict.removeNode(0);
    isAbsent(dict, 0);

    dict.removeNode(37);
    isAbsent(dict, 37);

    dict.removeNode(22);
    isAbsent(dict, 22);

    isPresent(dict, 4, "Stephen");
    isPresent(dict, 9, "Edward");
    isPresent(dict, 1, "William");
    isPresent(dict, 24, "James");
    isPresent(dict, 26, "Charles");
    isPresent(dict, 19, "Henry");
    isPresent(dict, 31, "Anne");
    isPresent(dict, 23, "Elizabeth");
    isPresent(dict, 42, "Elizabeth");
    isPresent(dict, -1, "Edward");
}

// Test case for inserting many nodes and then attempting to remove a node that doesn't exist.
TEST(RemoveTests, InsertMany_RemoveAbsent) {
    Dictionary dict;
    insertTestData(dict);

    dict.removeNode(6);
    isAbsent(dict, 6);

    isPresent(dict, 22, "Mary");
    isPresent(dict, 4, "Stephen");
    isPresent(dict, 9, "Edward");
    isPresent(dict, 1, "William");
    isPresent(dict, 0, "Harold");
    isPresent(dict, 24, "James");
    isPresent(dict, 26, "Charles");
    isPresent(dict, 19, "Henry");
    isPresent(dict, 31, "Anne");
    isPresent(dict, 23, "Elizabeth");
    isPresent(dict, 37, "Victoria");
    isPresent(dict, 42, "Elizabeth");
    isPresent(dict, -1, "Edward");
}

// These tests need verifying and completing to ensure they work.
TEST(CopyConstructorTests, CopyConstructorFullyCopies)
{
    Dictionary dict1; // Create a new Dictionary instance.
    insertTestData(dict1); // Insert test data.

    Dictionary dict2(dict1); // Create a new Dictionary instance using the copy constructor.

    // Verify that the copy constructor has fully copied the dictionary.
    isPresent(dict2, 22, "Mary");
    isPresent(dict2, 4, "Stephen");
    isPresent(dict2, 9, "Edward");
    isPresent(dict2, 1, "William");
    isPresent(dict2, 0, "Harold");
    isPresent(dict2, 24, "James");
    isPresent(dict2, 26, "Charles");
    isPresent(dict2, 19, "Henry");
	isPresent(dict2, 31, "Anne");
    isPresent(dict2, 23, "Elizabeth");
    isPresent(dict2, 37, "Victoria");
    isPresent(dict2, 42, "Elizabeth");
    isPresent(dict2, -1, "Edward");
}

TEST(CopyConstructorTests, CopyConstructorDoesNotDeleteSource)
{
    Dictionary dict1; // Create a new Dictionary instance.
    insertTestData(dict1); // Insert test data.

    Dictionary dict2(dict1); // Create a new Dictionary instance using the copy constructor.

    // Verify that the copy constructor has not deleted the source dictionary.
    isPresent(dict1, 22, "Mary");
	isPresent(dict1, 4, "Stephen");
    isPresent(dict1, 9, "Edward");
    isPresent(dict1, 1, "William");
    isPresent(dict1, 0, "Harold");
    isPresent(dict1, 24, "James");
    isPresent(dict1, 26, "Charles");
    isPresent(dict1, 19, "Henry");
    isPresent(dict1, 31, "Anne");
    isPresent(dict1, 23, "Elizabeth");
    isPresent(dict1, 37, "Victoria");
    isPresent(dict1, 42, "Elizabeth");
    isPresent(dict1, -1, "Edward");
}

TEST(CopyConstructorTests, CopyConstructorIsDeep)
{
    Dictionary dict1; // Create a new Dictionary instance.
    insertTestData(dict1); // Insert test data.

    Dictionary dict2(dict1); // Create a new Dictionary instance using the copy constructor.

    dict1.insertNode(2, "William"); // Insert a new node into the source dictionary.
    isPresent(dict1, 2, "William"); // Verify that the new node is present in the source dictionary.
    isAbsent(dict2, 2); // Verify that the new node is not present in the copied dictionary.

    dict2.insertNode(3, "Henry"); // Insert a new node into the copied dictionary.
	isPresent(dict2, 3, "Henry"); // Verify that the new node is present in the copied dictionary.
    isAbsent(dict1, 3); // Verify that the new node is not present in the source dictionary.

    dict1.removeNode(24); // Remove a node from the source dictionary.
    isAbsent(dict1, 24); // Verify that the node is not present in the source dictionary.
    isPresent(dict2, 24, "James"); // Verify that the node is still present in the copied dictionary.

    dict2.removeNode(26); // Remove a node from the copied dictionary.
    isAbsent(dict2, 26); // Verify that the node is not present in the copied dictionary.
    isPresent(dict1, 26, "Charles"); // Verify that the node is still present in the source dictionary.
}

// Test for rotateLeft.
TEST(RotationTests, RotateLeft) {
    Dictionary dict;
    insertTestData(dict);

    Dictionary::KeyType key = 22;
    dict.rotateLeft(key);

    // Verify the structure after rotation.
    Node* root = dict.getRoot();
    Node* leftChild = dict.getLeftChild(root->data);
    Node* rightChild = dict.getRightChild(root->data);

    // Check if the root and its children are as expected after rotation.
	EXPECT_EQ(root->data, 37);
    EXPECT_EQ(leftChild ? leftChild->data : -1, 22);
    EXPECT_EQ(rightChild ? rightChild->data : -1, 42);
}

// Test for rotateRight.
TEST(RotationTests, RotateRight) {
    Dictionary dict;
    insertTestData(dict);

    Dictionary::KeyType key = 22;
    dict.rotateRight(key);

    // Verify the structure after rotation.
    Node* root = dict.getRoot();
    Node* leftChild = dict.getLeftChild(root->data);
    Node* rightChild = dict.getRightChild(root->data);

    // Check if the root and its children are as expected after rotation.
    EXPECT_EQ(root->data, 0);
    EXPECT_EQ(leftChild ? leftChild->data : -1, -1);
    EXPECT_EQ(rightChild ? rightChild->data : -1, 22);
}

// Test case for fully moving a dictionary.
// This test checks if all elements are correctly moved to a new dictionary.
TEST(MoveConstructorTests, MoveConstructorFullyMoves) {
    Dictionary dict1;
    insertTestData(dict1); // Insert test data into dict1.

    Dictionary dict2(std::move(dict1)); // Move dict1 into dict2.

    // Check if all elements are present in dict2.
    isPresent(dict2, 22, "Mary");
    isPresent(dict2, 4, "Stephen");
    isPresent(dict2, 9, "Edward");
    isPresent(dict2, 1, "William");
    isPresent(dict2, 0, "Harold");
    isPresent(dict2, 24, "James");
    isPresent(dict2, 26, "Charles");
    isPresent(dict2, 19, "Henry");
    isPresent(dict2, 31, "Anne");
    isPresent(dict2, 23, "Elizabeth");
    isPresent(dict2, 37, "Victoria");
    isPresent(dict2, 42, "Elizabeth");
    isPresent(dict2, -1, "Edward");
}

// Test case for checking if the move constructor steals resources from the source.
// This test verifies that the source dictionary is empty after the move.
TEST(MoveConstructorTests, MoveConstructorSteals) {
    Dictionary* dictPtr;
    {
        Dictionary dict1;
        insertTestData(dict1); // Insert test data into dict1.

        // Move dict1 into a new dictionary pointed by dictPtr.
        dictPtr = new Dictionary(std::move(dict1));

        // Check if dict1 is empty after the move.
        isAbsent(dict1, 22);
        isAbsent(dict1, 4);
        isAbsent(dict1, 9);
        isAbsent(dict1, 1);
        isAbsent(dict1, 0);
        isAbsent(dict1, 24);
        isAbsent(dict1, 26);
        isAbsent(dict1, 19);
        isAbsent(dict1, 31);
        isAbsent(dict1, 23);
        isAbsent(dict1, 37);
        isAbsent(dict1, 42);
        isAbsent(dict1, -1);

        // Note: dict1 gets deleted here (end of scope).
    }

    // Check if all elements are present in the dictionary pointed by dictPtr.
    isPresent(*dictPtr, 22, "Mary");
    isPresent(*dictPtr, 4, "Stephen");
    isPresent(*dictPtr, 9, "Edward");
    isPresent(*dictPtr, 1, "William");
    isPresent(*dictPtr, 0, "Harold");
    isPresent(*dictPtr, 24, "James");
    isPresent(*dictPtr, 26, "Charles");
    isPresent(*dictPtr, 19, "Henry");
    isPresent(*dictPtr, 31, "Anne");
    isPresent(*dictPtr, 23, "Elizabeth");
    isPresent(*dictPtr, 37, "Victoria");
    isPresent(*dictPtr, 42, "Elizabeth");
    isPresent(*dictPtr, -1, "Edward");


    delete dictPtr; // Clean up dynamically allocated memory.
}

// Test case for fully copying a dictionary.
TEST(CopyAssignmentTests, CopyAssignmentFullyCopies) {
    Dictionary dict1;
    insertTestData(dict1);

    Dictionary dict2;
    dict2 = dict1; // Copy assignment.

    // Check if all elements are present in dict2
    isPresent(dict2, 22, "Mary");
    isPresent(dict2, 4, "Stephen");
    isPresent(dict2, 9, "Edward");
    isPresent(dict2, 1, "William");
    isPresent(dict2, 0, "Harold");
    isPresent(dict2, 24, "James");
    isPresent(dict2, 26, "Charles");
    isPresent(dict2, 19, "Henry");
    isPresent(dict2, 31, "Anne");
    isPresent(dict2, 23, "Elizabeth");
    isPresent(dict2, 37, "Victoria");
    isPresent(dict2, 42, "Elizabeth");
    isPresent(dict2, -1, "Edward");
}

// Test case for checking if the copy assignment overwrites existing data.
TEST(CopyAssignmentTests, CopyAssignmentOverwrites) {
    Dictionary dict1;
    insertTestData(dict1);

    Dictionary dict2;
    dict2.insertNode(22, "Jane");
    dict2.insertNode(2, "William");

    dict1 = dict2; // Copy assignment.

    // Check if dict1 only contains elements from dict2
    isAbsent(dict1, 4);
    isAbsent(dict1, 9);
    isAbsent(dict1, 1);
    isAbsent(dict1, 0);
    isAbsent(dict1, 24);
    isAbsent(dict1, 26);
    isAbsent(dict1, 19);
    isAbsent(dict1, 31);
    isAbsent(dict1, 23);
    isAbsent(dict1, 37);
    isAbsent(dict1, 42);
    isAbsent(dict1, -1);
    
    isPresent(dict1, 2, "William");
    isPresent(dict1, 22, "Jane");
}

// Test case for checking that copy assignment does not reverse copy.
TEST(CopyAssignmentTests, CopyAssignmentDoesNotReverseCopy) {
    Dictionary dict1;
    insertTestData(dict1);

    Dictionary dict2;
    dict2.insertNode(22, "Jane");
    dict2.insertNode(2, "William");

    dict2 = dict1; // Copy assignment.

    // Check if dict1 does not contain elements only in dict2.
    isAbsent(dict1, 2);
}

// Test case for checking deep copy in copy assignment.
TEST(CopyAssignmentTests, CopyAssignmentIsDeep) {
    Dictionary dict1;
    insertTestData(dict1);

    Dictionary dict2;
    dict2 = dict1; // Copy assignment.

    dict1.insertNode(2, "William");
    isPresent(dict1, 2, "William");
    isAbsent(dict2, 2);

    dict2.insertNode(3, "Henry");
    isPresent(dict2, 3, "Henry");
    isAbsent(dict1, 3);

    dict1.removeNode(24);
    isAbsent(dict1, 24);
    isPresent(dict2, 24, "James");

    dict2.removeNode(26);
    isAbsent(dict2, 26);
    isPresent(dict1, 26, "Charles");
}

// Test case for checking self-assignment.
TEST(CopyAssignmentTests, CopySelfAssignment) {
    Dictionary dict;
    insertTestData(dict);

    dict = dict; // Self-assignment.
    isPresent(dict, 24, "James");
    isPresent(dict, 26, "Charles");
    isAbsent(dict, 2);
}

// Test case for fully moving a dictionary
TEST(MoveAssignmentTests, MoveAssignmentFullyMoves) {
    Dictionary dict1;
    insertTestData(dict1);

    Dictionary dict2;
    dict2 = std::move(dict1); // Move assignment.

    // Check if all elements are present in dict2
    isPresent(dict2, 22, "Mary");
    isPresent(dict2, 4, "Stephen");
    isPresent(dict2, 9, "Edward");
    isPresent(dict2, 1, "William");
    isPresent(dict2, 0, "Harold");
    isPresent(dict2, 24, "James");
    isPresent(dict2, 26, "Charles");
    isPresent(dict2, 19, "Henry");
    isPresent(dict2, 31, "Anne");
    isPresent(dict2, 23, "Elizabeth");
    isPresent(dict2, 37, "Victoria");
    isPresent(dict2, 42, "Elizabeth");
    isPresent(dict2, -1, "Edward");
}

// Test case for checking if the move assignment steals resources
TEST(MoveAssignmentTests, MoveAssignmentSteals) {
    Dictionary dict1, dict2;
    insertTestData(dict1);

    dict2 = std::move(dict1); // Move assignment.

    // Check if dict1 is empty after the move
    isAbsent(dict1, 22);
    isAbsent(dict1, 4);
    isAbsent(dict1, 9);
    isAbsent(dict1, 1);
    isAbsent(dict1, 0);
    isAbsent(dict1, 24);
    isAbsent(dict1, 26);
    isAbsent(dict1, 19);
    isAbsent(dict1, 31);
    isAbsent(dict1, 23);
    isAbsent(dict1, 37);
    isAbsent(dict1, 42);
    isAbsent(dict1, -1);
}

// Test case for checking if the move assignment overwrites existing data
TEST(MoveAssignmentTests, MoveAssignmentOverwrites) {
    Dictionary dict1;
    insertTestData(dict1);

    Dictionary dict2;
    dict2.insertNode(22, "Jane");
    dict2.insertNode(2, "William");

    dict1 = std::move(dict2); // Move assignment.

    // Check if dict1 only contains elements from dict2
    isAbsent(dict1, 4);
    isAbsent(dict1, 9);
    isAbsent(dict1, 1);
    isAbsent(dict1, 0);
    isAbsent(dict1, 24);
    isAbsent(dict1, 26);
    isAbsent(dict1, 19);
    isAbsent(dict1, 31);
    isAbsent(dict1, 23);
    isAbsent(dict1, 37);
    isAbsent(dict1, 42);
    isAbsent(dict1, -1);

    isPresent(dict1, 2, "William");
}

// Test case for checking that move assignment is not a shallow copy
TEST(MoveAssignmentTests, MoveAssignmentIsNotShallowCopy) {
    Dictionary dict1;
    insertTestData(dict1);

    Dictionary dict2;
    dict2 = std::move(dict1); // Move assignment.

    dict1.removeNode(19);
    dict1.removeNode(23);
    isPresent(dict2, 19, "Henry");
    isPresent(dict2, 23, "Elizabeth");
}

// Test case for checking self-assignment with move assignment
TEST(MoveAssignmentTests, MoveSelfAssignment) {
    Dictionary dict;
    insertTestData(dict);

    dict = std::move(dict); // Self-assignment with move assignment.

    isPresent(dict, 24, "James");
    isPresent(dict, 26, "Charles");
}

// Test case for removing no elements
TEST(RemoveIfTests, RemoveNone) {
    Dictionary dict;
    insertTestData(dict);

    dict.removeIf([](int k) { return false; });

    // Check if all elements are still present
    isPresent(dict, 22, "Mary");
    isPresent(dict, 4, "Stephen");
    isPresent(dict, 9, "Edward");
    isPresent(dict, 1, "William");
    isPresent(dict, 0, "Harold");
    isPresent(dict, 24, "James");
    isPresent(dict, 26, "Charles");
    isPresent(dict, 19, "Henry");
    isPresent(dict, 31, "Anne");
    isPresent(dict, 23, "Elizabeth");
    isPresent(dict, 37, "Victoria");
    isPresent(dict, 42, "Elizabeth");
    isPresent(dict, -1, "Edward");
}

// Test case for removing all elements
TEST(RemoveIfTests, RemoveAll) {
    Dictionary dict;
    insertTestData(dict);

    dict.removeIf([](int k) { return true; });

    // Check if all elements are removed
    isAbsent(dict, 22);
    isAbsent(dict, 4);
    isAbsent(dict, 9);
    isAbsent(dict, 1);
    isAbsent(dict, 0);
    isAbsent(dict, 24);
    isAbsent(dict, 26);
    isAbsent(dict, 19);
    isAbsent(dict, 31);
    isAbsent(dict, 23);
    isAbsent(dict, 37);
    isAbsent(dict, 42);
    isAbsent(dict, -1);
}

// Test case for removing elements with odd keys
TEST(RemoveIfTests, RemoveOddKeys) {
    Dictionary dict;
    insertTestData(dict);

    dict.removeIf([](int k) { return k % 2 != 0; });

    // Check if odd key elements are removed and even key elements are present
    isPresent(dict, 22, "Mary");
    isPresent(dict, 4, "Stephen");
    isPresent(dict, 0, "Harold");
    isPresent(dict, 24, "James");
    isPresent(dict, 26, "Charles");
    isPresent(dict, 42, "Elizabeth");

    isAbsent(dict, 9);
    isAbsent(dict, 1);
    isAbsent(dict, 19);
    isAbsent(dict, 31);
    isAbsent(dict, 23);
    isAbsent(dict, 37);
    isAbsent(dict, -1);
}