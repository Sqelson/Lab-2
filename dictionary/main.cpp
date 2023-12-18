#include <iostream>
#include "dictionary.h"

int main()
{
	// The following displays the entries in the tree, and the tree itself. Useful for visualizing the tree and testing purposes.
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

	// The following is for rotation testing, only uncomment one at a time.

	Dictionary::KeyType key = 22;
	dict.rotateLeft(key);

	std::cout << ("Here is the tree, post-rotate left.") << std::endl;
	dict.displayTree();

	// Dictionary::KeyType key = 22;
	// dict.rotateRight(key);

	// std::cout << ("Here is the tree, post-rotate right.") << std::endl;
	// dict.displayTree();

}
