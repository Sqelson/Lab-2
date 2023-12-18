#pragma once
#include <iostream>
#include <vector>
#include "Node.h"

class Dictionary {
public:
    using KeyType = int;
    using ItemType = std::string;

    Dictionary(); // Default constructor
    ~Dictionary(); // Destructor
    Dictionary(const Dictionary& other); // Copy constructor

    void displayEntries(); // Function to display entries in the tree
    void displayTree(); // Function to display the tree structure

    ItemType* lookupNode(KeyType key); // Lookup a node with the specified key
    void insertNode(KeyType key, ItemType value); // Insert a node with the specified key and value
    void removeNode(KeyType key); // Remove a node with the specified key
    std::vector<int> inOrderTraversal(); // Perform in-order traversal of the tree

private:
    Node* head_; // Pointer to the root node

    bool isLeaf(Node* node); // Helper function to check if a node is a leaf
    void displayEntriesWorker(Node* node); // Recursive worker function for displayEntries
    void displayTreeWorker(Node* node, std::string indent); // Recursive worker function for displayTree
    ItemType* lookupNodeWorker(Node* node, KeyType key); // Recursive worker function for lookupNode
    Node* insertNodeWorker(Node*& node, KeyType key, ItemType value); // Recursive worker function for insertNode
    void removeNodeWorker(Node*& node, KeyType key); // Recursive worker function for removeNode
    void inOrderTraversalWorker(Node* node, std::vector<int>& keys); // Recursive worker function for inOrderTraversal
    void deepDeleteWorker(Node* node); // Recursive worker function for deep deletion of nodes
    Node* deepCopyWorker(Node* node); // Recursive worker function for deep copying of nodes
};
