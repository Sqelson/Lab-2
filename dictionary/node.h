#pragma once
#include <string>

struct Node {
    int data = 0; // key initialized to 0
    std::string value = ""; // value initialized to an empty string
    Node* left = nullptr;  // pointer to the left child node initialized to nullptr
    Node* right = nullptr;  // pointer to the right child node initialized to nullptr

    // Default constructor
    Node() = default;

    // Constructor to initialize data and value based on passed arguments
    Node(int key, std::string val) : data(key), value(val) {}
};