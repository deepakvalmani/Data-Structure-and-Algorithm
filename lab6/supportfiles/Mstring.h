#pragma once

#include <iostream>
#include <stdexcept>
#include "avl.hpp"

// Mutable string: the characters are the values of an AVL<double, char>
// in inorder (see the lab handout).
class Mstring
{
private:
    AVL<double, char> st_;

public:
    // Length of the string.
    int size()
    {
        // TODO
        return st_.size();
        // placeholder return value
    }

    // Return the i-th character (0-based).
    char get(int i)
    {
        // TODO
        return st_.get(st_.select(i));
        // placeholder return value
    }

    // Insert c so that it becomes the i-th character (0 <= i <= size()).
    void insert(int i, char c)
    {
        if (i < 0 || i > size())
            throw std::out_of_range("Invalid index");

        double key;

        if (size() == 0)
        {
            key = 0.0;
        }
        else if (i == 0)
        {
            key = st_.select(0) - 1.0;
        }
        else if (i == size())
        {
            key = st_.select(size() - 1) + 1.0;
        }
        else
        {
            double left = st_.select(i - 1);
            double right = st_.select(i);
            key = left + (right - left) / 2.0;
        }

        st_.put(key, c);
    }

    // Delete the i-th character.
    void remove(int i)
    {
        // TODO
        st_.remove(st_.select(i));
    }

    // Print the entire string.
    void print()
    {
        // TODO
        for (auto it = st_.begin(); it != st_.end(); ++it)
        {
            std::cout << it->second << " ";
        }
        std::cout << std::endl;
    }
};
