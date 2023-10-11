#pragma once
#include <iostream>

struct Node
{
    int data = 0; // key initialized to 0
    std::string value = ""; // value initialized to an empty string
    Node* left = nullptr;  // pointer to the left child node initialized to nullptr
    Node* right = nullptr;  // pointer to the right child node initialized to nullptr

    // Default constructor
    Node() = default;

    // Constructor to initialize data and value based on passed arguments
    Node(int key, std::string val) : data(key), value(val) {}
};

class Dictionary
{
public:
    // Default constructor initializing head_ to nullptr
    Dictionary() : head_(nullptr) {}

    using KeyType = int;
    using ItemType = std::string;

    void displayEntries();  // function to display entries in the tree, this is the wrapper function that provides the public API.

    void displayTree();  // function to display the tree, this is the wrapper function that provides the public API.

    ItemType* lookup(KeyType key) {
        return lookupWorker(head_, key);  // start recursion at the root of the tree
    }

    void insert(KeyType key, ItemType value) {
        head_ = insertWorker(head_, key, value);  // Call the recursive worker function
    }

private:
    Node* head_;  // pointer to root node initialized to nullptr
    bool isLeaf(Node*);  // helper function to check if node is a leaf

    void displayEntriesWorker(Node*);  // helper function to display entries in the tree, this is the recursive function that does the actual work.

    void displayTreeWorker(Node* node, std::string indent);  // helper function to display the tree, this is the recursive function that does the actual work.

    ItemType* lookupWorker(Node* node, KeyType key) const {
        if (node == nullptr) {
            return nullptr;  // base case: key not found
        }
        if (key == node->data) {
            return &node->value;  // base case: key found
        }
        else if (key < node->data) {
            return lookupWorker(node->left, key);  // recursive case: go left
        }
        else {
            return lookupWorker(node->right, key);  // recursive case: go right
        }
    }

    Node* insertWorker(Node* node, KeyType key, ItemType value) {
        if (node == nullptr) {
            // Base case: We've found the correct position in the tree, 
            // so create a new node and return it
            return new Node(key, value);
        }

        if (key == node->data) {
            // If the key already exists, update the value
            node->value = value; 
        }
        else if (key < node->data) {
            // If the key is smaller, go to the left subtree
            node->left = insertWorker(node->left, key, value); // recursive call, update the left child pointer
        }
        else {
            // If the key is larger, go to the right subtree
            node->right = insertWorker(node->right, key, value); // recursive call, update the right child pointer
        }

        return node;  // Return the (possibly updated) current node
    }
};