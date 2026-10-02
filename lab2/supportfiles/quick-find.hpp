#pragma once

#include <iostream>
#include <vector>

class QuickFindUF {
private:
    std::vector<int> leader;

public:
    QuickFindUF(int n) : leader(n) {
        for (int i = 0; i < n; i++)
            leader[i] = i;
    }

    int find(int p) {
        return leader[p];
    }

    void unify(int p, int q) {
        int pLeader = leader[p];
        int qLeader = leader[q];
        if (pLeader == qLeader) return;
        for (int i = 0; i < leader.size(); i++)
            if (leader[i] == pLeader)
                leader[i] = qLeader;
    }
};