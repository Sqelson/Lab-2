#include <iostream>
#include "dictionary.h"

int main()
{
	Dictionary dict;

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

	std::cout << ("Here are the entries in the tree.") << std::endl;
	dict.displayEntries();
	std::cout << ("Here is the tree.") << std::endl;
	dict.displayTree();
}

bool Dictionary::isLeaf(Node* theNode)
{
    return (theNode == nullptr);
}

void Dictionary::displayEntries()
{
	displayEntriesWorker(head_); // call the worker function on the root pointer to start the recursion
}

void Dictionary::displayEntriesWorker(Node* currentNode)
{
	if (currentNode == nullptr) return; // (1) base case: if the current node is null, return

	std::cout << "Key = " << currentNode->data << ", Value = " << currentNode->value << std::endl; // (A) code for processing a node during a pre-order traversal goes here
	displayEntriesWorker(currentNode->left);  // (2) recursively call the worker function on the left child pointer here
	// (B) code for processing a node during an in-order traversal would go here (cut and paste the code from (A) above)
	displayEntriesWorker(currentNode->right);  // (3) recursively call the worker function on the right child pointer here
	// (C) code for processing a node during a post-order traversal goes here (cut and paste the code from (A) above)
}

void Dictionary::displayTree() {
	displayTreeWorker(head_, ""); // call the worker function on the root pointer to start the recursion
}

void Dictionary::displayTreeWorker(Node* node, std::string indent) {
	if (node == nullptr) // Base case: if the current node is null, display a leaf node and return.
	{
		std::cout << indent << "*" << std::endl;
		return; 
	}
	std::cout << indent << "Key = " << node->data << ", Value = " << node->value << std::endl; // (A) code for processing a node during a pre-order traversal goes here
	indent += "    ";  // Increase indentation to distinguish child nodes.
	displayTreeWorker(node->left, indent);  // Recursive call for the left child with increased indentation.
	// (B) code for processing a node during an in-order traversal would go here (cut and paste the code from (A) above)
	displayTreeWorker(node->right, indent);  // Recursive call for the right child with increased indentation.
	// (C) code for processing a node during a post-order traversal goes here (cut and paste the code from (A) above)
}

// Define the copy constructor
Dictionary::Dictionary(const Dictionary& other) {
	// Initialize head_ to nullptr in the new object
	head_ = nullptr;
	// Perform a deep copy of the tree from 'other' using the recursive worker function
	head_ = deepCopyWorker(other.head_);
}

// Recursive worker function to perform deep copy
Node* Dictionary::deepCopyWorker(const Node* node) {
	if (node == nullptr) {
		return nullptr;  // Base case: If the original tree is empty, return nullptr
	}

	// Create a new node with the same data and value as the original node
	Node* newNode = new Node(node->data, node->value);

	// Recursively copy the left and right subtrees
	newNode->left = deepCopyWorker(node->left);
	newNode->right = deepCopyWorker(node->right);

	return newNode;
}