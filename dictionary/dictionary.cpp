#include "dictionary.h"
#include "node.h"

// Constructor
Dictionary::Dictionary() : head_(nullptr) {}

// Destructor
Dictionary::~Dictionary() {
    deepDeleteWorker(head_);
}

// Copy Constructor
Dictionary::Dictionary(const Dictionary& other) {
    head_ = deepCopyWorker(other.head_);
}

// Check if a node is a leaf (null)
bool Dictionary::isLeaf(Node* theNode) {
    return (theNode == nullptr);
}

// Display all entries in the dictionary
void Dictionary::displayEntries() {
    displayEntriesWorker(head_);
}

// Recursive worker for displaying entries
void Dictionary::displayEntriesWorker(Node* currentNode) {
    if (isLeaf(currentNode)) return;
    std::cout << "Key = " << currentNode->data << ", Value = " << currentNode->value << std::endl;
    displayEntriesWorker(currentNode->left);
    displayEntriesWorker(currentNode->right);
}

// Display the structure of the tree
void Dictionary::displayTree() {
    displayTreeWorker(head_, "");
}

// Recursive worker for displaying the tree
void Dictionary::displayTreeWorker(Node* node, std::string indent) {
    if (isLeaf(node)) {
        std::cout << indent << "*" << std::endl;
        return;
    }
    std::cout << indent << "Key = " << node->data << ", Value = " << node->value << std::endl;
    indent += "    ";
    displayTreeWorker(node->left, indent);
    displayTreeWorker(node->right, indent);
}

// Lookup a node by key
Dictionary::ItemType* Dictionary::lookupNode(KeyType key) {
    return lookupNodeWorker(head_, key);
}

// Recursive worker for node lookup
Dictionary::ItemType* Dictionary::lookupNodeWorker(Node* node, KeyType key) {
    if (isLeaf(node)) {
        return nullptr;
    }
    if (key == node->data) {
        return &node->value;
    }
    if (key < node->data) {
        return lookupNodeWorker(node->left, key);
    }
    return lookupNodeWorker(node->right, key);
}

// Insert a node
void Dictionary::insertNode(KeyType key, ItemType value) {
    head_ = insertNodeWorker(head_, key, value);
}

// Recursive worker for node insertion
Node* Dictionary::insertNodeWorker(Node*& node, KeyType key, ItemType value) {
    if (isLeaf(node)) {
        return new Node(key, value);
    }
    if (key == node->data) {
        node->value = value;
    }
    else if (key < node->data) {
        node->left = insertNodeWorker(node->left, key, value);
    }
    else {
        node->right = insertNodeWorker(node->right, key, value);
    }
    return node;
}

// Remove a node
void Dictionary::removeNode(KeyType key) {
    removeNodeWorker(head_, key);
}

// Recursive worker for node removal
void Dictionary::removeNodeWorker(Node*& node, KeyType key) {
    // Implementation of removeNodeWorker...
}

// In-order traversal
std::vector<int> Dictionary::inOrderTraversal() {
    std::vector<int> keys;
    inOrderTraversalWorker(head_, keys);
    return keys;
}

// Recursive worker for in-order traversal
void Dictionary::inOrderTraversalWorker(Node* node, std::vector<int>& keys) {
    if (!isLeaf(node)) {
        inOrderTraversalWorker(node->left, keys);
        keys.push_back(node->data);
        inOrderTraversalWorker(node->right, keys);
    }
}

// Recursive worker for deep deletion
void Dictionary::deepDeleteWorker(Node* node) {
    if (isLeaf(node)) {
        return;
    }
    deepDeleteWorker(node->left);
    deepDeleteWorker(node->right);
    delete node;
}

// Recursive worker for deep copy
Node* Dictionary::deepCopyWorker(Node* node) {
    if (isLeaf(node)) {
        return nullptr;
    }
    Node* newNode = new Node(node->data, node->value);
    newNode->left = deepCopyWorker(node->left);
    newNode->right = deepCopyWorker(node->right);
    return newNode;
}
