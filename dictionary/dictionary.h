#pragma once
#include <iostream>
struct Node 
{
    int data; // key

    std::string value; // value

    Node* left;  // pointer to the left child node
    Node* right;  // pointer to the right child node

    // Default constructor initializing data to 0 and child pointers to nullptr
    Node() : data(0), left(nullptr), right(nullptr) {}
};

class Dictionary
{
private:
    Node* head_ /*= nullptr*/;

public:
    Dictionary() // default constructor
    {
        head_ = nullptr; // empty list
    }

    std::string* lookup(int key) {
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

    void insert(int key, std::string value)
    {
        // Create a new node using the default constructor and then set the data and value fields
        Node* newNode = new Node();
        newNode->data = key;
        newNode->value = value;

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
        if (key < parent->data)
        {
            parent->left = newNode;  // insert new node as left child of parent
        }
        else
        {
            parent->right = newNode;  // insert new node as right child of parent
        }
    }
};

