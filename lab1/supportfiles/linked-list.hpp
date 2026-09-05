#pragma once
#include <string>

// =============================================================================
// Part B: Singly linked List of characters
// Complete the implementation of the LinkedList class below.
// You will need to implement the push_front, push_back, and pop_front methods.
// =============================================================================

class LinkedList
{
private:
    struct Node
    {
        char data;
        Node *next;
        Node(int val) : data(val), next(nullptr) {}
    };
    Node *head;
    int _size;

public:
    LinkedList() : head(nullptr), _size(0) {}
    ~LinkedList()
    {
        while (!empty())
            pop_front();
    }

    bool empty() const { return _size == 0; }
    int size() const { return _size; }

    // Return the contents of char list as a string
    std::string to_string() const
    {
        std::string result(_size, '\0');
        int i = 0;
        Node *current = head;
        while (current != nullptr)
        {
            result[i++] = current->data;
            current = current->next;
        }
        return result;
    }

    void push_front(int value)
    {
        // Implement push_front to add a new node with the given value at the front of the list.
        // Handle the case when the list is empty and update head, tail, and _size accordingly.
        // ----- TODO -------

        Node *new_node = new Node(value);
        new_node->next = head;
        head = new_node;
        _size++;
    }

    char pop_front()
    {
        // Implement pop_front to remove the node at the front of the list.
        // If the list is empty, handle it appropriately (e.g., return '\0' or throw an exception).
        // ----- TODO -------
        if (empty())
        {
            throw "Empty List";
        }
        Node *temp = head;
        char value = head->data;

        head = head->next;

        delete temp;
        _size--;

        return value;
        // return '\0'; // Placeholder return value, should be replaced with actual implementation
    }

    char front() const
    {
        // Implement front to return the value of the node at the front of the list.
        // If the list is empty, handle it appropriately (e.g., return '\0' or throw an exception).
        // ----- TODO -------
        if (empty())
        {
            throw "Empty List";
        }
        return head->data;
        //return '\0'; // Placeholder return value, should be replaced with actual implementation
    }
};
