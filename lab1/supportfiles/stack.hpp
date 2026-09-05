#pragma once
#include <string>
#include "resizable-array.hpp"
#include "linked-list.hpp"

// =============================
// Part C: Stack Implementations
// =============================

// --- Stack using ResizableArray ---
class ArrayStack
{
private:
    ResizableArray arr;

public:
    // Return true if the stack is empty, false otherwise
    bool empty() const { return arr.empty(); }

    // Return the contents of char stack as a string
    std::string to_string()
    {
        return arr.to_string();
    }

    void push(char value)
    {
        // Add a new character to the top of the stack.
        // ----- TODO -------
        arr.push_back(value);
    }

    char pop()
    {
        // Remove and return the top character from the stack.
        // If the stack is empty, handle it appropriately (e.g., throw an exception).
        // ----- TODO -------
        if (empty())
        {
            throw "Empty Stack";
        }
        char value = arr.back(arr.size() - 1);
        arr.pop_back();
        return value;
        // return '\0'; // Placeholder return value, should be replaced with actual implementation
    }

    char top() const
    {
        if (empty())
        {
            throw "Empty Stack";
        }
        return arr.back(arr.size() - 1);
        
        // Return the top element of the stack without removing it.
        // If the stack is empty, handle it appropriately (e.g., throw an exception).
        // ----- TODO -------
        // return '\0'; // Placeholder return value, should be replaced with actual implementation
    }
};

// --- Stack using LinkedList ---
class LinkedListStack
{
private:
    LinkedList list;

public:
    // Return true if the stack is empty, false otherwise
    bool empty() const { return list.empty(); }

    // Return the contents of char stack as a string
    std::string to_string() const
    {
        return list.to_string();
    }

    void push(char value)
    {
        list.push_front(value);
        // Add a new character to the top of the stack.
        // ----- TODO -------
    }

    void pop()
    {
        if (empty())
        {
            throw "Empty Stack";
        }
        list.pop_front();
        // Remove the top character from the stack.
        // If the stack is empty, handle it appropriately (e.g., throw an exception).
        // ----- TODO -------
    }

    char top() const
    {
        if (empty())
        {
            throw "Empty Stack";
        }
        return list.front();
        // Return the top element of the stack without removing it.
        // If the stack is empty, handle it appropriately (e.g., throw an exception).
        // ----- TODO -------
        //return '\0'; // Placeholder return value, should be replaced with actual implementation
    }
};
