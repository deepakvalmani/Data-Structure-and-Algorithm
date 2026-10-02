#pragma once

#include <vector>
#include <queue>

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

// Number of nodes in the tree (provided; see lab handout).
int size(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + size(root->left) + size(root->right);
}

// Free every node in the tree (provided).
void destroy(Node* root) {
    if (root == nullptr) return;
    destroy(root->left);
    destroy(root->right);
    delete root;
}

// ---------------------------------------------------------------
// Part A & B: Level order
// ---------------------------------------------------------------

// Part A: keys of the tree level by level, left to right.
std::vector<int> levelOrder(Node* root) {
    // TODO: use a std::queue<Node*>. Start with the root; repeatedly
    // remove a node, record its key, and add its non-null children
    // (left, then right) to the queue.
    return {}; // placeholder return value
}

// Part B: rebuild the BST whose level order traversal is `keys` and return
// its root (nullptr if keys is empty).
Node* buildFromLevelOrder(const std::vector<int>& keys) {
    // TODO: use either approach from the lab handout:
    //   1. insert the keys one by one into an empty BST, or
    //   2. a queue of (node, min, max) entries for O(n) time.
    return nullptr; // placeholder return value
}

// ---------------------------------------------------------------
// Part C: Recursive methods
// Conventions: the root has depth 0; an empty tree has height -1.
// ---------------------------------------------------------------

// Maximum depth of any node in the tree.
int height(Node* root) {
    // TODO
    return -2; // placeholder return value
}

// Number of nodes with an odd key.
int sizeOdd(Node* root) {
    // TODO
    return -1; // placeholder return value
}

// At every node, do the left and right subtrees have the same height?
bool isPerfectlyBalanced(Node* root) {
    // TODO
    return false; // placeholder return value
}

// Is every node semi-balanced? (see lab handout for the definition)
bool isSemiBalanced(Node* root) {
    // TODO
    return false; // placeholder return value
}

// Number of nodes at depth d.
int sizeAtDepth(Node* root, int d) {
    // TODO
    return -1; // placeholder return value
}

// Number of nodes whose depth is < d.
int sizeAboveDepth(Node* root, int d) {
    // TODO
    return -1; // placeholder return value
}

// Number of nodes whose depth is > d.
int sizeBelowDepth(Node* root, int d) {
    // TODO
    return -1; // placeholder return value
}
