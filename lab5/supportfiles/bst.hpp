#pragma once

#include <vector>
#include <queue>

struct Node
{
    int key;
    Node *left;
    Node *right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

// Number of nodes in the tree (provided; see lab handout).
int size(Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    return 1 + size(root->left) + size(root->right);
}

// Free every node in the tree (provided).
void destroy(Node *root)
{
    if (root == nullptr)
        return;
    destroy(root->left);
    destroy(root->right);
    delete root;
}

// ---------------------------------------------------------------
// Part A & B: Level order
// ---------------------------------------------------------------

// Part A: keys of the tree level by level, left to right.
std::vector<int> levelOrder(Node *root)
{
    // TODO: use a std::queue<Node*>. Start with the root; repeatedly
    // remove a node, record its key, and add its non-null children
    // (left, then right) to the queue.
    // placeholder return value
    std::vector<int> vec;
    if (root == nullptr)
        return vec;

    std::queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
        Node *curr = q.front();
        q.pop();
        vec.push_back(curr->key);

        if (curr->left)
            q.push(curr->left);
        if (curr->right)
            q.push(curr->right);
    }
    return vec;
}

// Part B: rebuild the BST whose level order traversal is `keys` and return
// its root (nullptr if keys is empty).
Node *buildFromLevelOrder(const std::vector<int> &keys)
{
    // TODO: use either approach from the lab handout:
    //   1. insert the keys one by one into an empty BST, or
    //   2. a queue of (node, min, max) entries for O(n) time.
    Node *head = nullptr;
    for (int x : keys)
    {
        Node *newNode = new Node(x);

        if (!head)
        {
            head = newNode;
            continue;
        }
        Node *curr = head;
        while (true)
        {
            if (x < curr->key)
            {
                if (curr->left == nullptr)
                {
                    curr->left = newNode;
                    break;
                }
                curr = curr->left;
            }
            else
            {
                if (curr->right == nullptr)
                {
                    curr->right = newNode;
                    break;
                }
                curr = curr->right;
            }
        }
    }
    return head; // placeholder return value
}

// ---------------------------------------------------------------
// Part C: Recursive methods
// Conventions: the root has depth 0; an empty tree has height -1.
// ---------------------------------------------------------------

// Maximum depth of any node in the tree.
int height(Node *root)
{
    // TODO
    if (root == nullptr)
        return -1;
    return 1 + std::max(height(root->left), height(root->right));

    // placeholder return value
}

// Number of nodes with an odd key.
int sizeOdd(Node *root)
{
    // TODO
    if (root == nullptr)
        return 0;
    if (root->key % 2 == 0)
        return 0 + sizeOdd(root->left) + sizeOdd(root->right);
    if (root->key % 2 != 0)
        return 1 + sizeOdd(root->left) + sizeOdd(root->right);
    // placeholder return value
}

// At every node, do the left and right subtrees have the same height?
bool isPerfectlyBalanced(Node *root)
{
    // TODO
    if (root == nullptr)
        return true;
return height(root->left) == height(root->right) &&
           isPerfectlyBalanced(root->left) &&
           isPerfectlyBalanced(root->right);    // placeholder return value
} 

// Is every node semi-balanced? (see lab handout for the definition)
bool isSemiBalanced(Node *root)
{
    // TODO
    if (root == nullptr)
        return true;
    int size1 = size(root->left);
    int size2 = size(root->right);
    bool current = (std::max(size1, size2) + 1) <= 2 * (std::min(size1, size2) + 1);
    return current && isSemiBalanced(root->left) && isSemiBalanced(root->right);
    // placeholder return value
}

// Number of nodes at depth d.
int sizeAtDepth(Node *root, int d)
{
    if (root == nullptr)
        return 0;
    if (d == 0)
        return 1;
    // TODO

    return sizeAtDepth(root->left, d - 1) + sizeAtDepth(root->right, d - 1); // placeholder return value
}

// Number of nodes whose depth is < d.
int sizeAboveDepth(Node *root, int d)
{
    // TODO
    if (root == nullptr)
        return 0;
    if (d <= 0)
        return 0;

    return 1 + sizeAboveDepth(root->left, d - 1) + sizeAboveDepth(root->right, d - 1); // placeholder return value
}

// Number of nodes whose depth is > d.
int sizeBelowDepth(Node *root, int d)
{
    if (root == nullptr)
        return 0;
    if (d < 0)
        return size(root);

    return sizeBelowDepth(root->left, d - 1) + sizeBelowDepth(root->right, d - 1); // placeholder return value
}
