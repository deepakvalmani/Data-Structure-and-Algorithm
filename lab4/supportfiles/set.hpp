#pragma once

#include <stdexcept>
#include <vector>

template <typename Key>
class Set
{
private:
    std::vector<Key> keys_; // kept sorted in ascending order, no duplicates

    // Return the index of the smallest element in keys_ that is >= key
    // (i.e. where key belongs, or already sits, in the sorted array).
    // Return keys_.size() if key is larger than every element.
    // Do NOT use std::lower_bound / std::binary_search / std::find.

    int binarySearch(const Key &key) const
    {
        // TODO: implement binary search over keys_.
        //
        int st = 0;
        int end = keys_.size();
        while (st < end)
        {
            int mid = st + (end - st) / 2;

            if (keys_[mid] < key)
                st = mid + 1;
            else
                end = mid;
        }
        return st; // placeholder return value, replace with actual implementation
    }

public:
    Set() {}

    int size() const
    {
        return keys_.size();
    }

    bool contains(const Key &key) const
    {
        // TODO: use binarySearch to check whether key is present.
        //
        int idx = binarySearch(key);
        return (idx < keys_.size() && keys_[idx] == key); // placeholder return value
    }

    void add(const Key &key)
    {
        // TODO: find the insertion point with binarySearch. If key is
        // already present, do nothing. Otherwise shift every element
        // from that point onward up by one slot and place key there.
        // Do not use vector::insert.
        int idx = binarySearch(key);
        int last_idx = size() - 1;

        if (idx < size() && keys_[idx] == key)
            return;

        keys_.push_back(key);

        while (last_idx >= idx)
        {
            keys_[last_idx + 1] = keys_[last_idx];
            last_idx--;
        }

        keys_[idx] = key;
    }

    void remove(const Key &key)
    {
        // TODO: find key with binarySearch. If present, shift every
        // element above it down by one slot to close the gap.
        // Do not use vector::erase.
        int idx = binarySearch(key);
        int last_idx = size() - 1;
        if (idx < 0 || idx >= size() || keys_[idx] != key)
            return;

        for (int i = idx; i < size() - 1; i++)
        {
            keys_[i] = keys_[i + 1];
        }

        keys_.pop_back();
    }

    Key ceiling(const Key &key) const
    {
        // TODO: smallest key in the set >= given key.
        // Throw std::runtime_error if no such key exists.
        int idx = binarySearch(key);
        if (idx >= keys_.size())
            throw std::runtime_error("no ceiling for key");

        return keys_[idx];
    }

    int rank(const Key &key) const
    {
        // TODO: number of keys in the set strictly smaller than key.
        //
        return binarySearch(key);
    }

    Key select(int i) const
    {
        // TODO: the i-th largest key in the set (see lab handout).
        // Throw std::runtime_error if i is out of range.
        if (i < 0 || i >= keys_.size())
            throw std::runtime_error("index out of range");
        return keys_[size() - 1 - i];
    }

    Key min() const
    {
        // TODO: return the smallest key in the set.
        // Throw std::runtime_error if the set is empty.
        if (size() <= 0)
            throw std::runtime_error("set is empty");
        return keys_[0];
    }

    // iterator support
    using iterator = typename std::vector<Key>::const_iterator;
    iterator begin() const { return keys_.begin(); }
    iterator end() const { return keys_.end(); }
};
