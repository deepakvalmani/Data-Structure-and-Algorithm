#pragma once

#include <vector>

class UF
{
private:
    std::vector<int> parent, size;

public:
    UF(int n) : parent(n), size(n)
    {
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int find(int i)
    {
        // TODO: return the root of the set containing i.
        // Use path compression: while searching, make every node
        // point directly to the root (or use recursion).
        if (parent[i] == i)
        {
            return i;
        }
        parent[i] = find(parent[i]);
        return parent[i];
    }

    void unify(int p, int q)
    {
        // TODO: merge the sets containing p and q.
        // Use union by size: attach the root of the smaller tree
        // under the root of the larger tree.
        int p_val = find(p);
        int q_val = find(q);
        if (p_val == q_val)
        {
            return;
        }
        if (size[p_val] > size[q_val])
        {
            parent[q_val] = p_val;
            size[p_val] += size[q_val];
        }
        else
        {
            parent[p_val] = q_val;
            size[q_val] += size[p_val];
        }
    }
};
