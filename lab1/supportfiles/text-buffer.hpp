#pragma once
#include <string>
#include "stack.hpp"

// =============================
// Part D: Text Buffer
// =============================

// --- TextBuffer using ArrayStack ---
class TextBufferArray
{
private:
    ArrayStack left;  // characters to the left of cursor
    ArrayStack right; // characters to the right of cursor

public:
    void insert(char c)
    {
        left.push(c);
        // Insert character c at the cursor position (i.e., push onto left stack)
        // ----- TODO -------
    }

    void remove()
    {
        // Remove the character at the cursor position (i.e., pop from right stack)
        // Handle the case when the right stack is empty (i.e., no character to remove)
        // ----- TODO -------
        if (!right.empty())
        {
            right.pop();
        }
    }

    void moveLeft()
    {
        // Move the cursor one position to the left (i.e., pop from left stack and push onto right stack)
        // Handle the case when the left stack is empty (i.e., cursor is at the beginning of the text)
        // ----- TODO -------
        if (!left.empty())
        {
            char c = left.pop();
            right.push(c);
        }
    }

    void moveRight()
    {
        // Move the cursor one position to the right (i.e., pop from right stack and push onto left stack)
        // Handle the case when the right stack is empty (i.e., cursor is at the end of the text)
        // ----- TODO -------
        if (!right.empty())
        {
            char c = right.pop();
            left.push(c);
        }
    }

    std::string getText()
    {
        std::string leftText = left.to_string();
        std::string rightText = right.to_string();

        std::string result = leftText;

        for (int i = rightText.size() - 1; i >= 0; i--)
        {
            result += rightText[i];
        }

        return result;

        // Return the current text in the buffer as a string
        // This may involve combining the contents of the left and right stacks
        // ----- TODO -------
        // return ""; // Placeholder return value, should be replaced with actual implementation
    }
};

// --- TextBuffer using LinkedListStack ---
class TextBufferList
{
private:
    LinkedListStack left;
    LinkedListStack right;

public:
    void insert(char c)
    {
        // Insert character c at the cursor position (i.e., push onto left stack)
        // ----- TODO -------
        left.push(c);
    }

    void remove()
    {
        // Remove the character at the cursor position (i.e., pop from right stack)
        // Handle the case when the right stack is empty (i.e., no character to remove)
        // ----- TODO -------
        if (!right.empty())
        {
            right.pop();
        }
    }

    void moveLeft()
    {
        // Move the cursor one position to the left (i.e., pop from left stack and push onto right stack)
        // Handle the case when the left stack is empty (i.e., cursor is at the beginning of the text)
        // ----- TODO -------
        if (!left.empty())
        {
            char c = left.top();
            left.pop();
            right.push(c);
        }
    }

    void moveRight()
    {
        // Move the cursor one position to the right (i.e., pop from right stack and push onto left stack)
        // Handle the case when the right stack is empty (i.e., cursor is at the end of the text)
        // ----- TODO -------
        if (!right.empty())
        {
            char c = right.top();
            right.pop();
            left.push(c);
        }
    }

    std::string getText()
    {
        std::string leftText = left.to_string();
        std::string rightText = right.to_string();
        std::string result;
        for (int i = leftText.size() - 1; i >= 0; i--)
        {
            result += leftText[i];
        }
        result += rightText;
        return result;
        // Return the current text in the buffer as a string
        // This may involve combining the contents of the left and right stacks
        // ----- TODO -------
        // return ""; // Placeholder return value, should be replaced with actual implementation
    }
};
