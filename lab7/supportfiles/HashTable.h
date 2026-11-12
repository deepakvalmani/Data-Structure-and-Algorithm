#pragma once

#include <list>
#include <string>
#include <vector>

// A set of strings, implemented as a hash table with separate chaining.
class HashTable
{
private:
    std::vector<std::list<std::string>> table_; // table_[i] is the chain of keys with index i
    int n_ = 0;                                 // number of keys

    // Polynomial hash code of key: s[0]*31^(k-1) + s[1]*31^(k-2) + ... + s[k-1],
    // computed by Horner's rule (the arithmetic wraps around modulo 2^32).
    unsigned int hashCode(const std::string &key) const
    {
        // TODO
        int k = key.length();
        unsigned int h = 0;

        for (int i = 0; i < k; i++)
        {
            h += static_cast<unsigned int>(key[i]) * 31 ^ (k - 1 - i);
        }

        return h;
    }

    // Index of the chain for key, between 0 and tableSize() - 1.
    int index(const std::string &key) const
    {
        return hashCode(key) % table_.size();
    }

    // Rehash every key into a new table with the given number of chains.
    void resize(int capacity)
    {
        // TODO
        std::vector<std::list<std::string>> table1(nextPrime(capacity));
        std::swap(table_, table1);
        for (auto& chain : table1) {
            for(auto &k : chain) {
                table_[index(k)].push_front(k);
            }
        }
    }

    static bool isPrime(int p)
    {
        if (p < 2)
            return false;
        for (int i = 2; i * i <= p; i++)
            if (p % i == 0)
                return false;
        return true;
    }

public:
    // Smallest prime >= n.
    static int nextPrime(int n)
    {
        while (!isPrime(n))
            n++;
        return n;
    }

    // Create an empty table with nextPrime(capacity) chains.
    explicit HashTable(int capacity = 101) : table_(nextPrime(capacity)) {}

    // Insert key if it is not already present. If the table is full
    // (size() == tableSize()), first resize to nextPrime(2 * tableSize()) chains.
    void insert(const std::string &key)
    {
        // TODO
        if (tableSize() == size())
        {
            resize(2 * size());
        }
        if (!contains(key))
        {
            int idx = index(key);
            table_[idx].push_front(key);
            n_++;
        }

    }

    // Return true if key is present.
    bool contains(const std::string &key) const
    {
        // TODO
        int idx = index(key);
        if (idx > 0 && idx < tableSize())
        {
            for (std::string s : table_[idx])
            {
                if (s == key)
                    return true;
            }
        }
        return false; // placeholder return value
    }

    int size() const { return n_; }
    bool empty() const { return n_ == 0; }
    int tableSize() const { return table_.size(); }
    double loadFactor() const { return double(n_) / table_.size(); }
};
