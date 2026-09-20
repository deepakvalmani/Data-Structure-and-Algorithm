#pragma once
#include <vector>
#include <stdexcept>
#include <utility>
#include <ctime>
#include <algorithm>

template <typename Key>
class MinPQ
{
private:
    std::vector<Key> pq; // Index 0 is unused

public:
    MinPQ() : pq(1) {}

    bool empty()
    {
        return pq.size() == 1;
    }

    int size()
    {
        return pq.size() - 1;
    }

    void insert(const Key &x)
    {
        // Insert new element at the end of the heap
        // and then swim it to restore heap order
        pq.push_back(x);
        swim(pq.size() - 1);
    }

    Key back(){return pq.back();}
    Key front(){return pq.front();}

    Key delMin()
    {
        // Add underflow check and resizing logic
        if (pq.size() == 1)
            throw std::runtime_error("Priority queue underflow");

        // Exchange the root of the heap with the last element
        // and then sink the new root to restore heap order
        std::swap(pq[1], pq.back());
        const auto min = std::move(pq.back());
        pq.pop_back();
        sink(1);
        return min;
    }
    Key deleteRandom()
    {
        if (pq.size() == 1)
            throw std::runtime_error("Priority queue underflow");

        srand(time(0));
        int x = rand() % size();
        std::swap(pq[x], pq.back());
        const auto random = std::move(pq.back());
        pq.pop_back();
        if (x > 1 && pq[x / 2] > pq[x])
        {
            swim(x);
        }
        else
        {
            sink(x);
        }

        return random;
    }

private:
    void swim(int k)
    {
        while (k > 1 && pq[k / 2] > pq[k])
        {
            std::swap(pq[k], pq[k / 2]);
            k = k / 2;
        }
    }

    void sink(int k)
    {
        int n = pq.size() - 1;
        while (2 * k <= n)
        {
            int j = 2 * k;
            if (j < n && pq[j] > pq[j + 1])
                j++;
            if (!(pq[k] > pq[j]))
                break;
            std::swap(pq[k], pq[j]);
            k = j;
        }
    }
};
