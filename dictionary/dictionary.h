#pragma once
#include <iostream>
#include <vector>
#include "Node.h"

class Dictionary {
public:
    using KeyType = int;
    using ItemType = std::string;

    Dictionary(); // Default constructor.

    // This set of declarations adheres to the rule of 5 (an extension of the rule of 3).
    ~Dictionary(); // Destructor.
    Dictionary(const Dictionary& other); // Copy constructor.
    Dictionary(Dictionary&& other); // Move constructor
	Dictionary& operator=(const Dictionary& other); // Copy assignment operator.
    Dictionary& operator=(Dictionary&& other); // Move assignment operator.

    void displayEntries(); // Displays entries in the tree.

    void displayTree(); // Displays the tree structure.

    ItemType* lookupNode(KeyType key); // Looks up a node with the specified key.

    void insertNode(KeyType key, ItemType value); // Inserts a node with the specified key and value.

    void removeNode(KeyType key); // Removes a node with the specified key.

    std::vector<int> inOrderTraversal(); // Performs in-order traversal of the tree.

    Node* getNode(KeyType key); // Gets a node by key.

    Node* getRoot(); // Gets the root node.
    Node* getLeftChild(KeyType key); // Gets the left child of a node.
    Node* getRightChild(KeyType key); // Gets the right child of a node.

    void rotateLeft(KeyType key); // Rotates left around a node.
    void rotateRight(KeyType key); // Rotates right around a node.

private:
    Node* head_; // Pointer to the root node.

    bool isLeaf(Node* node); // Checks if a node is a leaf.

    void displayEntriesWorker(Node* node); // Recursive worker for displayEntries.

    void displayTreeWorker(Node* node, std::string indent, bool isLeft); // Recursive worker for displayTree.

    ItemType* lookupNodeWorker(Node* node, KeyType key); // Recursive worker for lookupNode.

    Node* insertNodeWorker(Node*& node, KeyType key, ItemType value); // Recursive worker for insertNode.

    void removeNodeWorker(Node*& node, KeyType key); // Recursive worker for removeNode.
    Node* findMin(Node* node); // Finds the minimum node in a subtree.

    void inOrderTraversalWorker(Node* node, std::vector<int>& keys); // Recursive worker for inOrderTraversal.

    void deepDeleteWorker(Node* node); // Recursive worker for deep deletion of nodes.

    Node* deepCopyWorker(Node* node); // Recursive worker for deep copying of nodes.

    Node* getNodeWorker(Node* node, KeyType key); // Private helper for getNode.

    Node* getRootWorker(); // Private worker for getRoot.
    Node* getLeftChildWorker(Node* node); // Private worker for getLeftChild.
    Node* getRightChildWorker(Node* node); // Private worker for getRightChild.

    Node* rotateLeftWorker(Node* node); // Private worker for rotateLeft.
    Node* rotateRightWorker(Node* node); // Private worker for rotateRight.
};
