#include "dictionary.h"
#include "node.h"

bool Dictionary::isLeaf(Node* theNode)
{
	return (theNode == nullptr);
	// if the node is null, it is a leaf, this replaces the nullptr == theNode syntax for readability
}

void Dictionary::displayEntries()
{
	displayEntriesWorker(head_); // call the worker function on the root pointer to start the recursion
}

void Dictionary::displayEntriesWorker(Node* currentNode)
{
	if (isLeaf(currentNode)) return; // (1) base case: if the current node is null, return

	std::cout << "Key = " << currentNode->data << ", Value = " << currentNode->value << std::endl;
	// (A) code for processing a node during a pre-order traversal goes here
	displayEntriesWorker(currentNode->left); // (2) recursively call the worker function on the left child pointer here
	// (B) code for processing a node during an in-order traversal would go here (cut and paste the code from (A) above)
	displayEntriesWorker(currentNode->right);
	// (3) recursively call the worker function on the right child pointer here
	// (C) code for processing a node during a post-order traversal goes here (cut and paste the code from (A) above)
}

void Dictionary::displayTree()
{
	displayTreeWorker(head_, ""); // call the worker function on the root pointer to start the recursion
}

void Dictionary::displayTreeWorker(Node* node, std::string indent)
{
	if (isLeaf(node)) // Base case: if the current node is null, display a leaf node and return.
	{
		std::cout << indent << "*" << std::endl;
		return;
	}
	std::cout << indent << "Key = " << node->data << ", Value = " << node->value << std::endl;
	// (A) code for processing a node during a pre-order traversal goes here
	indent += "    "; // Increase indentation to distinguish child nodes.
	displayTreeWorker(node->left, indent); // Recursive call for the left child with increased indentation.
	// (B) code for processing a node during an in-order traversal would go here (cut and paste the code from (A) above)
	displayTreeWorker(node->right, indent); // Recursive call for the right child with increased indentation.
	// (C) code for processing a node during a post-order traversal goes here (cut and paste the code from (A) above).
}

// Define the copy constructor.
Dictionary::Dictionary(const Dictionary& other)
{
	// Initialize head_ to nullptr in the new object.
	head_ = nullptr;
	// Perform a deep copy of the tree from 'other' using the recursive worker function.
	head_ = deepCopyWorker(other.head_);
}

// Recursive worker function to perform deep copy.
Node* Dictionary::deepCopyWorker(Node* node)
{
	if (isLeaf(node))
	{
		return nullptr; // Base case: If the original tree is empty, return nullptr.
	}

	// Create a new node with the same data and value as the original node.
	auto newNode = new Node(node->data, node->value);

	// Recursively copy the left and right subtrees.
	newNode->left = deepCopyWorker(node->left);
	newNode->right = deepCopyWorker(node->right);

	return newNode;
}

// Rotate left around the given node
Node* Dictionary::rotateLeft(Node* node) {
	if (node == nullptr || node->right == nullptr) {
		return node; // Can't rotate
	}

	Node* newRoot = node->right; // New root will be the right child
	node->right = newRoot->left; // Update right child of old root
	newRoot->left = node; // Update left child of new root

	return newRoot; // Return new root
}

// Rotate right around the given node
Node* Dictionary::rotateRight(Node* node) {
	if (node == nullptr || node->left == nullptr) {
		return node; // Can't rotate
	}

	Node* newRoot = node->left; // New root will be the left child
	node->left = newRoot->right; // Update left child of old root
	newRoot->right = node; // Update right child of new root

	return newRoot; // Return new root
}
