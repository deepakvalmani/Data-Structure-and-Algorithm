#pragma once

#include <iostream>
#include <vector>

class QuickUnionUF {
private:
    std::vector<int> parent;

public:
    QuickUnionUF(int n) : parent(n) {
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int i) {
        while (i != parent[i])
            i = parent[i];
        return i;
    }

    void unify(int p, int q) {
        int i = find(p);
        int j = find(q);
        if (i == j) return;
        parent[i] = j;
    }
};