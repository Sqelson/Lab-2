#pragma once
#include <iostream>
struct Node 
{
    int data; // key

    std::string value; // value

    Node* next; // pointer to next node in list

    Node() : data(0), next(NULL) {} // default constructor
};

class Dictionary
{
private:
    Node* head_ /*= nullptr*/;

public:
    Dictionary() // default constructor
    {
        head_ = nullptr; // empty list
    }

    std::string* lookup(int key) {
        Node* curr = head_; // start at head of list

        while (curr != nullptr) // traverse list
        {
            if (curr->data == key) // key found in list
            {
                return &curr->value; // return pointer to value
            }

            curr = curr->next; // move to next node
        }

        return nullptr; // key not found in list
    }

    void insert(int key, std::string value) 
    {
        Node* curr = head_; // start at head of list

        while (curr != nullptr) // traverse list
        {
            if (curr->data == key) // key already exists in list
            {
                curr->value = value; // overwrite existing key with new value
                return;
            }

            if (curr->next == nullptr) // end of list
                break;

            curr = curr->next; // move to next node
        }

        // key not found in list, create new node at end of list
        Node* newNode = new Node();
        newNode->data = key; // copy key into new node
        newNode->value = value; // copy value into new node
        newNode->next = nullptr; // new node is last node in list

        if (curr != nullptr) // list not empty
            curr->next = newNode; // add new node to end of list
        else // list empty
            head_ = newNode; // new node is first node in list
     }
};

