#include <iostream>
#include "dictionary.h"

int main()
{
	Dictionary dict;

	dict.insert(22, "Jane");
	dict.insert(22, "Mary");
	dict.insert(0, "Harold");
	dict.insert(9, "Edward");
	dict.insert(37, "Victoria");
	dict.insert(4, "Matilda");
	dict.insert(26, "Oliver");
	dict.insert(42, "Elizabeth");
	dict.insert(19, "Henry");
	dict.insert(4, "Stephen");
	dict.insert(24, "James");
	dict.insert(-1, "Edward");
	dict.insert(31, "Anne");
	dict.insert(23, "Elizabeth");
	dict.insert(1, "William");
	dict.insert(26, "Charles");

	dict.displayEntries();
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