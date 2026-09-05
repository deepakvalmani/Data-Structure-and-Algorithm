#pragma once
#include <string>

// ============================================================================
// Part A: Resizable Array of characters
// Complete the implementation of the ResizableArray class below.
// You will need to implement the resize, push_back, pop_back, and get methods.
// ============================================================================
//
class ResizableArray
{
private:
    int _capacity; // Current capacity of the array
    int _size;     // Current number of elements in the array
    char *data;    // Pointer to the dynamically allocated array

    void resize(int newCapacity)
    { // Resizes the array to a new capacity
        // Implement the resize function to allocate a new array with newCapacity,
        // copy existing elements, and update _capacity and data pointer.
        // -------- TODO -------
        char *new_data = new char[newCapacity];
        for (int i = 0; i < _size; i++)
        {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        _capacity = newCapacity;
    }

public:
    ResizableArray() : _capacity(2), _size(0), data(new char[_capacity]) {}
    ~ResizableArray() { delete[] data; }

    // Return the current size of the array
    int size() const { return _size; };

    // Return true if the array is empty, false otherwise
    bool empty() const { return _size == 0; };

    // Return the contents of char array as a string
    std::string to_string() const
    {
        std::string result(_size, '\0');
        for (int i = 0; i < _size; ++i)
        {
            result[i] = data[i];
        }
        return result;
    }

    void push_back(char value)
    {
        // Add a new character to the end of the array.
        // If the array is full, call resize to double the capacity.
        // ----- TODO -------
        if (size() == _capacity)
        {
            resize(_capacity * 2);
        }
        data[_size] = value;
        _size++;
    }

    void pop_back()
    {
        // Remove the last character from the array.
        // If the array is less than a quarter full, call resize to halve the capacity.
        // ----- TODO -------
        if (empty())
        {
            throw "Empty Array";
        }
        _size--;
        if (size() < _capacity / 4)
        {
            resize(_capacity / 2);
        };
    }

    char back(int index) const
    {
        // Return the character at the specified index.
        // If index is out of bounds, handle it appropriately (e.g., throw an exception).
        // ----- TODO -------
        if (empty())
        {
            throw "Empty Array";
        }
        if (index < 0 || index >= _size)
        {
            throw "Out of bound";
        }
        return data[index];
        //return '\0'; // Placeholder return value, should be replaced with actual implementation
    }
};
