#pragma once

#include <vector>
#include <cassert>
#include <stdexcept>
#include <stack>
#include <queue>
#include <iostream>
#include <algorithm>

// AVL tree: a BST that keeps |height(left) - height(right)| <= 1 at every node,
// so its height is Theta(log n) and every operation below takes O(log n) time.
// Same interface as the BST from the lectures (bst.hpp), plus height().

template<typename Key, typename Value>
class AVL {
    struct Node {
        std::pair<const Key,Value> data;
        Node *left, *right;
        int count;   // number of nodes in the subtree rooted at this node
        int height;  // height of the subtree rooted at this node (leaf = 0)
        Node(Key k, Value v, int c=1)
            : data {k, v},
              left{nullptr}, right{nullptr},
              count{c}, height{0} {  }
    };

    Node* root;

    public:
    AVL() : root{nullptr} {  }
    ~AVL() { remove_all(root); }
    AVL(const AVL&) = delete;             // copying would share nodes
    AVL& operator=(const AVL&) = delete;

    private:
    void remove_all(Node* x) {
        if (x == nullptr) return;
        remove_all(x->left);
        remove_all(x->right);
        delete x;
    }

    // ---------------------------------------------------------------
    // AVL helpers
    // ---------------------------------------------------------------
    int height(Node* x) {
        return x == nullptr ? -1 : x->height;
    }

    int balanceFactor(Node* x) {
        return height(x->left) - height(x->right);
    }

    // Recompute height and count from the children (which must be correct).
    void update(Node* x) {
        x->height = 1 + std::max(height(x->left), height(x->right));
        x->count  = 1 + size(x->left) + size(x->right);
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T = x->right;
        x->right = y;
        y->left = T;
        update(y);
        update(x);
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T = y->left;
        y->left = x;
        x->right = T;
        update(x);
        update(y);
        return y;
    }

    // Restore the AVL property at x, whose subtrees are already AVL trees.
    Node* rebalance(Node* x) {
        update(x);
        int bf = balanceFactor(x);
        if (bf > 1) {                              // left-heavy
            if (balanceFactor(x->left) < 0)        //   LR -> turn into LL
                x->left = rotateLeft(x->left);
            return rotateRight(x);                 //   LL fix
        }
        if (bf < -1) {                             // right-heavy
            if (balanceFactor(x->right) > 0)       //   RL -> turn into RR
                x->right = rotateRight(x->right);
            return rotateLeft(x);                  //   RR fix
        }
        return x;                                  // already balanced
    }

    public:
    // Height of the tree (empty tree = -1, single node = 0).
    int height() {
        return height(root);
    }

    Value& get(const Key& key) {
        Node *x = root;
        while (x != nullptr) {
            if(key < x->data.first)
                x = x->left;
            else if (x->data.first < key)
                x = x->right;
            else
                return x->data.second;
        }
        throw std::out_of_range("Key not found");
    }

    void put(const Key& key, const Value& val) {
        root = put(root, key, val);
    }

    private:
    Node* put(Node* x, const Key& key, const Value& val)  {
        if (x == nullptr) return new Node(key, val, 1);

        if (key < x->data.first)
            x->left  = put(x->left,  key, val);
        else if (x->data.first < key)
            x->right = put(x->right, key, val);
        else {
            x->data.second = val;   // key already present: no structural change
            return x;
        }
        return rebalance(x);
    }

    public:
    Value& operator[](const Key& key) {
        root = ensure_key(root, key);
        return get(key);
    }

    private:
    Node* ensure_key(Node* x, const Key& key) {
        if (x == nullptr) return new Node(key, Value(), 1);

        if (key < x->data.first)
            x->left  = ensure_key(x->left,  key);
        else if (x->data.first < key)
            x->right = ensure_key(x->right, key);
        else
            return x;

        return rebalance(x);
    }


    public:
    const Key& min() {
        if (root == nullptr)
            throw std::out_of_range("called min() with empty symbol table");
        Node* x = min(root);
        return x->data.first;
    }

    private:
    Node* min(Node* x) {
        while (x->left != nullptr) x = x->left;
        return x;
    }

    public:
    const Key& floor(const Key& key) {
        return floor(root, key);
    }

    private:
    const Key& floor(Node* x, const Key& key, Node* champ=nullptr) {
        if (x == nullptr) {
            if(champ==nullptr)
                throw std::out_of_range("No such floor key");
            return champ->data.first;
        }

        if (key == x->data.first) return key;

        if (key < x->data.first)
            return floor(x->left, key, champ);

        return floor(x->right, key, x);
    }

    public:
    const Key& ceil(const Key& key) {
        return ceil(root, key);
    }

    private:
    const Key& ceil(Node* x, const Key& key, Node* champ=nullptr) {
        if (x == nullptr) {
            if(champ==nullptr)
                throw std::out_of_range("No such floor key");
            return champ->data.first;
        }

        if (key == x->data.first) return key;

        if (key < x->data.first)
            return ceil(x->left, key, x);

        return ceil(x->right, key, champ);
    }

    public:
    int size() {
        return size(root);
    }

    private:
    int size(Node* x) {
        if (x == nullptr) return 0;
        return x->count;
    }

    public:
    int rank(Key key) {
        return rank(root, key);
    }

    private:
    int rank(Node* x, const Key& key) {
        if (x == nullptr) return 0;

        if (key < x->data.first)
            return rank(x->left, key);
        else if (key > x->data.first)
            return 1 + size(x->left) + rank(x->right, key);
        else
            return size(x->left);
    }

    public:
    Key select(int k) {
        if (k < 0 || k >= size())
            throw std::out_of_range("called select() with invalid argument");

        Node* x = select(root, k);
        return x->data.first;
    }

    private:
    Node* select(Node* x, int k) {
        assert(x != nullptr);

        int t = size(x->left);
        if (t > k)
            return select(x->left,  k);
        else if (t < k)
            return select(x->right, k-t-1);
        else
            return x;
    }

    public:
    void removeMin() {
        if(root == nullptr)
            throw std::out_of_range("Symbol table underflow");
        Node* d = nullptr;
        root = removeMin(root, d);
        delete d;
    }

    private:
    Node* removeMin(Node* x, Node*& d) {
        if (x->left == nullptr) {
            Node* right = x->right;
            d = x; // to be removed
            return right;
        }
        x->left  = removeMin(x->left, d);
        return rebalance(x);
    }

    public:
    void remove(const Key& key) {
        root = remove(root, key);
    }

    private:
    Node* remove(Node* x, const Key& key) {
        if (x == nullptr) throw std::out_of_range("Key not found");

        if (key < x->data.first)
            x->left  = remove(x->left,  key);

        else if (x->data.first < key)
            x->right = remove(x->right, key);

        else {
            if (x->right == nullptr || x->left  == nullptr) {
                Node* ch = x->right==nullptr ? x->left : x->right;
                delete x;
                return ch;
            }

            // two children: replace x by its successor s
            Node* s = nullptr;
            x->right = removeMin(x->right, s);
            s->left = x->left;
            s->right = x->right;

            delete x;
            x = s;
        }
        return rebalance(x);   // rebalance every node on the path back up
    }

    public:
    class iterator {
        std::vector<Node*> stack;
        public:
        iterator(Node* r) {
            while(r) {
                stack.push_back(r);
                r = r->left;
            }
        }
        iterator& operator++() {
            if(stack.empty())
                throw std::out_of_range("Incrementing end iterator");
            Node* x = stack.back();
            stack.pop_back();
            if(x->right) {
                x = x->right;
                while(x) {
                    stack.push_back(x);
                    x = x->left;
                }
            }
            return *this;
        }
        bool operator!=(const iterator& other) const {
            return stack != other.stack;
        }
        std::pair<const Key, Value>& operator*() {
            if(stack.empty())
                throw std::out_of_range("Dereferencing end iterator");
            Node* x = stack.back();
            return x->data;
        }

        std::pair<const Key, Value>* operator->() {
            if(stack.empty())
                throw std::out_of_range("Dereferencing end iterator");
            Node* x = stack.back();
            return &(x->data);
        }

    };

    public:
    iterator begin() { return iterator(root); }
    iterator end()   { return iterator(nullptr); }

    public:
    void print() { print(root);}

    private:
    void print(Node* x) {
        // In-order traversal
        if (x == nullptr) return;
        print(x->left);
        std::cout << "[" << x->data.first << ":" << x->data.second << "]  ";
        print(x->right);
    }

    public:
    void in_order() {
        std::stack<Node*> q;
        Node* x = root;
        while(x || !q.empty()) {
            while(x) {
                q.push(x);
                x = x->left;
            }
            x = q.top(); q.pop();
            std::cout << "[" << x->data.first << ":" << x->data.second << "]  ";
            x = x->right;
        }
    }

    public:
    void level_order() {
        if (root == nullptr) return;
        std::queue<Node*> q;
        q.push(root);
        while(!q.empty()) {
            Node* x = q.front(); q.pop();
            std::cout << "[" << x->data.first << ":" << x->data.second << "]  ";
            if(x->left)  q.push(x->left);
            if(x->right) q.push(x->right);
        }
    }
};
