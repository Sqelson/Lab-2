#pragma once
#include <string>

struct Node
{
	int data = 0; // Key initialized to 0.
	std::string value = ""; // Value initialized to an empty string.
	Node* left = nullptr; // Pointer to the left child node initialized to nullptr.
	Node* right = nullptr; // Pointer to the right child node initialized to nullptr.

	// Default constructor.
	Node() = default;

	// Constructor to initialize data and value based on passed arguments.
	Node(int key, std::string val) : data(key), value(val)
	{
	}
};
