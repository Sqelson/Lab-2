#include "dictionary.h"
#include "node.h"

// Constructor.
Dictionary::Dictionary() : head_(nullptr) {}

// Destructor.
Dictionary::~Dictionary() {
    deepDeleteWorker(head_);
}

// Copy Constructor.
Dictionary::Dictionary(const Dictionary& other) {
    head_ = deepCopyWorker(other.head_);
}

// Copy assignment operator.
Dictionary& Dictionary::operator=(const Dictionary& other) {
    if (this == &other) {
        // Check for self-assignment.
        return *this;
    }

    // Delete the current tree to prevent memory leaks.
    deepDeleteWorker(head_);

    // Perform a deep copy of the other dictionary's tree.
    head_ = deepCopyWorker(other.head_);

    // Return a reference to this object.
    return *this;
}

// Move constructor
Dictionary::Dictionary(Dictionary&& other) noexcept
    : head_(other.head_) { // Transfer the root node pointer
    other.head_ = nullptr; // Set the source object's root node pointer to nullptr
}

// Move assignment operator.
Dictionary& Dictionary::operator=(Dictionary&& other) noexcept {
    if (this != &other) {
        // Check for self-assignment
        deepDeleteWorker(head_); // Delete current tree to prevent memory leaks

        head_ = other.head_; // Transfer the root node pointer from the source object
        other.head_ = nullptr; // Set the source object's root node pointer to nullptr
    }
    return *this; // Return a reference to this object
}

// Check if a node is a leaf (null).
bool Dictionary::isLeaf(Node* theNode) {
    return (theNode == nullptr);
}

// Display all entries in the dictionary.
void Dictionary::displayEntries() {
    displayEntriesWorker(head_);
}

// Recursive worker for displaying entries.
void Dictionary::displayEntriesWorker(Node* currentNode) {
    if (isLeaf(currentNode)) return;
    std::cout << "Key = " << currentNode->data << ", Value = " << currentNode->value << std::endl;
    displayEntriesWorker(currentNode->left);
    displayEntriesWorker(currentNode->right);
}

// Display the structure of the tree.
void Dictionary::displayTree() {
    // Start the recursive display from the root node.
    displayTreeWorker(head_, "", false); // Root node has no indentation.
}

// Recursive worker for displaying the tree.
void Dictionary::displayTreeWorker(Node* node, std::string indent, bool isLeft) {
    if (node == nullptr) {
        // If the node is null, do not print anything (no leaf representation).
        return;
    }

    // Print the branch leading to this node.
    if (!indent.empty()) {
        // Print the indentation followed by a branch symbol.
        // Use "|-- " for left children and "\\-- " for right children.
        std::cout << indent.substr(0, indent.length() - 2) << (isLeft ? "|-- " : "\\-- ");
    }

    // Print the current node (key and value).
    std::cout << "Key = " << node->data << ", Value = " << node->value << std::endl;

    // Construct the new indent for the next level of the tree.
    // For left children, extend the vertical line; for right children, extend with spaces.
    std::string newIndent = indent + (isLeft ? "|   " : "    ");

    // Recursively display the left and right children.
    displayTreeWorker(node->left, newIndent, true);  // Left child with updated indent.
    displayTreeWorker(node->right, newIndent, false); // Right child with updated indent.
}


// Lookup a node by key.
Dictionary::ItemType* Dictionary::lookupNode(KeyType key) {
    return lookupNodeWorker(head_, key);
}

// Recursive worker for node lookup.
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

// Insert a node.
void Dictionary::insertNode(KeyType key, ItemType value) {
    head_ = insertNodeWorker(head_, key, value);
}

// Recursive worker for node insertion.
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

// Remove a node.
void Dictionary::removeNode(KeyType key) {
    removeNodeWorker(head_, key);
}

// Recursive worker for node removal.
void Dictionary::removeNodeWorker(Node*& node, KeyType key) {
    if (node == nullptr) {
        return; // Node not found, do nothing.
    }

    if (key < node->data) {
        // Key is smaller, go to the left subtree.
        removeNodeWorker(node->left, key);
    }
    else if (key > node->data) {
        // Key is larger, go to the right subtree.
        removeNodeWorker(node->right, key);
    }
    else {
        // Node found, remove it.
        if (node->left == nullptr) {
            // Node has only right child or no children.
            Node* temp = node->right;
            delete node;
            node = temp;
        }
        else if (node->right == nullptr) {
            // Node has only left child.
            Node* temp = node->left;
            delete node;
            node = temp;
        }
        else {
            // Node has two children.
            // Find the in-order successor (smallest in the right subtree).
            Node* successor = findMin(node->right);
            // Copy the in-order successor's data to this node.
            node->data = successor->data;
            // Remove the in-order successor.
            removeNodeWorker(node->right, successor->data);
        }
    }
}

// Helper function to find the minimum node in a subtree.
Node* Dictionary::findMin(Node* node) {
    Node* current = node;
    // Keep going left until we reach a leaf.
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

// In-order traversal.
std::vector<int> Dictionary::inOrderTraversal() {
    std::vector<int> keys;
    inOrderTraversalWorker(head_, keys);
    return keys;
}

// Recursive worker for in-order traversal.
void Dictionary::inOrderTraversalWorker(Node* node, std::vector<int>& keys) {
    if (!isLeaf(node)) {
        inOrderTraversalWorker(node->left, keys);
        keys.push_back(node->data);
        inOrderTraversalWorker(node->right, keys);
    }
}

// Recursive worker for deep deletion.
void Dictionary::deepDeleteWorker(Node* node) {
    if (isLeaf(node)) {
        return;
    }
    deepDeleteWorker(node->left);
    deepDeleteWorker(node->right);
    delete node;
}

// Recursive worker for deep copy.
Node* Dictionary::deepCopyWorker(Node* node) {
    if (isLeaf(node)) {
        return nullptr;
    }
    Node* newNode = new Node(node->data, node->value);
    newNode->left = deepCopyWorker(node->left);
    newNode->right = deepCopyWorker(node->right);
    return newNode;
}

// Public method to rotate left around a node with the given key.
void Dictionary::rotateLeft(KeyType key) {
    Node* node = getNode(key); // Retrieve the node to rotate around.
    if (node != nullptr) {
        head_ = rotateLeftWorker(node); // Perform the rotation.
    }
}

// Public method to rotate right around a node with the given key.
void Dictionary::rotateRight(KeyType key) {
    Node* node = getNode(key); // Retrieve the node to rotate around.
    if (node != nullptr) {
        head_ = rotateRightWorker(node); // Perform the rotation.
    }
}

// Private worker function to perform left rotation.
Node* Dictionary::rotateLeftWorker(Node* node) {
    if (node == nullptr || node->right == nullptr) {
        return node; // Can't rotate.
    }

    Node* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;

    return newRoot; // Return the new root after rotation.
}

// Private worker function to perform right rotation.
Node* Dictionary::rotateRightWorker(Node* node) {
    if (node == nullptr || node->left == nullptr) {
        return node; // Can't rotate.
    }

    Node* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;

    return newRoot; // Return the new root after rotation.
}

// Public method to get a node by its key.
// This is the entry point for external calls to find a node.
Node* Dictionary::getNode(KeyType key) {
    // Start the search from the root of the tree.
    return getNodeWorker(head_, key);
}

// Private recursive helper function to find a node by its key.
Node* Dictionary::getNodeWorker(Node* node, KeyType key) {
    // Base case: If the current node is null (leaf), return nullptr.
    // This means the key is not found in the tree.
    if (isLeaf(node)) {
        return nullptr;
    }

    // If the current node's key matches the search key, return the current node.
    // This means the node with the specified key has been found.
    if (key == node->data) {
        return node;
    }

    // If the search key is less than the current node's key, continue the search in the left subtree.
    // This is because, in a binary search tree, smaller keys are in the left subtree.
    if (key < node->data) {
        return getNodeWorker(node->left, key);
    }

    // If the search key is greater than the current node's key, continue the search in the right subtree.
    // This is because, in a binary search tree, larger keys are in the right subtree.
    return getNodeWorker(node->right, key);
}

// Public method to get the root node.
Node* Dictionary::getRoot() {
    return getRootWorker();
}

// Public method to get the left child of a node.
Node* Dictionary::getLeftChild(KeyType key) {
    Node* node = getNode(key);
    return getLeftChildWorker(node);
}

// Public method to get the right child of a node.
Node* Dictionary::getRightChild(KeyType key) {
    Node* node = getNode(key);
    return getRightChildWorker(node);
}

// Private worker function to get the root node.
Node* Dictionary::getRootWorker() {
    return head_;
}

// Private worker function to get the left child of a node.
Node* Dictionary::getLeftChildWorker(Node* node) {
    return node ? node->left : nullptr;
}

// Private worker function to get the right child of a node.
Node* Dictionary::getRightChildWorker(Node* node) {
    return node ? node->right : nullptr;
}
