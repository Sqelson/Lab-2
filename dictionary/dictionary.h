#pragma once
#include <iostream>
#include <vector>
#include "Node.h"

struct Node;

class Dictionary
{
public:
	// Default constructor initializing head_ to nullptr
	Dictionary() : head_(nullptr)
	{
	}

	// Destructor to delete all nodes in the tree
	~Dictionary()
	{
		// Call the recursive function to delete all nodes
		deepDeleteWorker(head_);
	}

	// Copy constructor that performs a deep copy of the tree
	Dictionary(const Dictionary& other);

	using KeyType = int;
	using ItemType = std::string;

	void displayEntries();
	// function to display entries in the tree, this is the wrapper function that provides the public API.

	void displayTree(); // function to display the tree, this is the wrapper function that provides the public API.

	// Public function to initiate the lookup of a node with the specified key
	ItemType* lookupNode(KeyType key)
	{
		return lookupNodeWorker(head_, key); // start recursion at the root of the tree
	}

	// Public function to initiate the insertion of a node with the specified key and value
	void insertNode(KeyType key, ItemType value)
	{
		head_ = insertNodeWorker(head_, key, value); // Call the recursive worker function
	}

	// Public function to initiate the removal of a node with the specified key
	void removeNode(KeyType key)
	{
		removeNodeWorker(head_, key); // Call the recursive worker function starting at the root of the tree
	}

	std::vector<int> inOrderTraversal()
	{
		std::vector<int> keys;
		inOrderTraversalWorker(head_, keys);
		return keys;
	}

private:
	Node* head_; // pointer to root node initialized to nullptr
	bool isLeaf(Node*); // helper function to check if node is a leaf

	void displayEntriesWorker(Node*);
	// helper function to display entries in the tree, this is the recursive function that does the actual work.

	void displayTreeWorker(Node* node, std::string indent);
	// helper function to display the tree, this is the recursive function that does the actual work.

	ItemType* lookupNodeWorker(Node* node, KeyType key)
	{
		if (isLeaf(node))
		{
			return nullptr; // base case: key not found
		}
		if (key == node->data)
		{
			return &node->value; // base case: key found
		}
		if (key < node->data)
		{
			return lookupNodeWorker(node->left, key); // recursive case: go left
		}
		return lookupNodeWorker(node->right, key); // recursive case: go right
	}

	// Recursive worker function to insert a node with the specified key and value, also using a reference parameter now (&)!
	Node* insertNodeWorker(Node*& node, KeyType key, ItemType value)
	{
		if (isLeaf(node))
		{
			// Base case: We've found the correct position in the tree, 
			// so create a new node and return it
			return new Node(key, value);
		}

		if (key == node->data)
		{
			// If the key already exists, update the value
			node->value = value;
		}
		else if (key < node->data)
		{
			// If the key is smaller, go to the left subtree
			node->left = insertNodeWorker(node->left, key, value); // recursive call, update the left child pointer
		}
		else
		{
			// If the key is larger, go to the right subtree
			node->right = insertNodeWorker(node->right, key, value); // recursive call, update the right child pointer
		}

		return node; // Return the (possibly updated) current node
	}

	// Helper function to find the in-order successor of a node (the smallest node in its right subtree)
	void findMin(Node* node, Node*& parent, Node*& minNode)
	{
		parent = node; // Initialize the parent of the minNode as the current node
		minNode = node->right; // Start the search in the right subtree
		while (minNode->left != nullptr)
		{
			// Traverse to the leftmost node in the right subtree
			parent = minNode; // Update the parent of the minNode
			minNode = minNode->left; // Move to the left child
		}
	}

	// Recursive worker function to find and remove a node with the specified key
	void removeNodeWorker(Node*& node, KeyType key)
	{
		if (isLeaf(node))
		{
			return; // Key not found, do nothing
		}

		if (key == node->data)
		{
			// If the key matches the current node's data
			// Case 1: Node with only one child or no children
			if (node->left == nullptr || node->right == nullptr)
			{
				Node* tempNode = (node->left != nullptr) ? node->left : node->right; // Get the non-null child (if any)
				delete node; // Delete the current node, this is VERY IMPORTANT to prevent memory leaks
				node = tempNode; // Assign the non-null child to the current node's position
			}
			// Case 2: Node with two children
			else
			{
				Node* parentMinNode;
				Node* minNode;
				findMin(node, parentMinNode, minNode); // Find the in-order successor
				node->data = minNode->data; // Copy the in-order successor's data to the current node
				node->value = minNode->value; // Copy the in-order successor's value to the current node
				if (parentMinNode->left == minNode)
				{
					removeNodeWorker(parentMinNode->left, minNode->data);
					// Recursively remove the in-order successor in the left subtree
				}
				else
				{
					removeNodeWorker(parentMinNode->right, minNode->data);
					// Recursively remove the in-order successor in the right subtree
				}
			}
		}
		else if (key < node->data)
		{
			// If the key is less than the current node's data
			removeNodeWorker(node->left, key); // Recursively search for the key in the left subtree
		}
		else
		{
			// If the key is greater than the current node's data
			removeNodeWorker(node->right, key); // Recursively search for the key in the right subtree
		}
	}

	void inOrderTraversalWorker(Node* node, std::vector<int>& keys)
	{
		if (!isLeaf(node))
		{
			inOrderTraversalWorker(node->left, keys);
			keys.push_back(node->data);
			inOrderTraversalWorker(node->right, keys);
		}
	}

	// Recursive helper function to delete all nodes in the tree.
	void deepDeleteWorker(Node* node)
	{
		if (isLeaf(node))
		{
			return; // Base case: the tree (subtree) is empty, nothing to delete.
		}

		deepDeleteWorker(node->left); // Recursively delete the left subtree.
		deepDeleteWorker(node->right); // Recursively delete the right subtree.

		delete node; // Delete the current node.
	}

	Node* deepCopyWorker(Node* node); // Recursive helper function to perform a deep copy of the tree.

	// Rotation functions
	Node* rotateLeft(Node* node);
	Node* rotateRight(Node* node);
};
