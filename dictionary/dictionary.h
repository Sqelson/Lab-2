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
private:
    Node* head_;  // pointer to root node initialized to nullptr

public:
    // Default constructor initializing head_ to nullptr
    Dictionary() : head_(nullptr) {}

    using KeyType = int;
    using ItemType = std::string;

    ItemType* lookup(KeyType key) {
        Node* curr = head_;  // start at the root of the tree

        while (curr != nullptr)  // traverse tree
        {
            if (curr->data == key)  // key found in tree
            {
                return &curr->value;  // return pointer to value
            }
            else if (key < curr->data)  // if sought key is less, go left
            {
                curr = curr->left;
            }
            else  // if sought key is greater, go right
            {
                curr = curr->right;
            }
        }
        return nullptr;  // key not found in tree
    }

    void insert(KeyType key, ItemType value)
    {
        Node* newNode = new Node(key, value);  // use constructor to initialize data and value

        if (head_ == nullptr)  // tree is empty
        {
            head_ = newNode;  // new node becomes the root of the tree
            return;
        }

        Node* curr = head_;  // start at the root of the tree
        Node* parent = nullptr;  // keep track of the parent node

        while (curr != nullptr)  // traverse tree
        {
            parent = curr;  // update parent to current node before moving to child

            if (key == curr->data)  // key already exists in tree
            {
                curr->value = value;  // overwrite existing key with new value
                delete newNode;  // delete the newly created node as it's not needed
                return;
            }
            else if (key < curr->data)  // if key is less, go left
            {
                curr = curr->left;
            }
            else  // if key is greater, go right
            {
                curr = curr->right;
            }
        }

        // key not found in tree, insert new node in correct position
        if (key < parent->data)  // if key is less than parent, insert as left child
        {
            parent->left = newNode;  // insert new node as left child of parent
        }
        else  // if key is greater than parent, insert as right child
        {
            parent->right = newNode;  // insert new node as right child of parent
        }
    }
};