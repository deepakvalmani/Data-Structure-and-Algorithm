#pragma once

#include <iostream>
#include <list>
#include <map>
#include <stdexcept>

// LRU cache of ints holding at most capacity items.
class LRU
{
private:
    int capacity_;
    std::list<int> order_;                        // items, most recently accessed first
    std::map<int, std::list<int>::iterator> pos_; // item -> its node in order_

public:
    LRU(int capacity) : capacity_(capacity) {}

    // Insert item if not already present, evicting the least recently
    // accessed item if the cache is over capacity; mark item as the most
    // recently accessed.
    void access(int item)
    {
        // TODO
        if (contains(item))
        {
            order_.erase(pos_[item]);
            order_.push_front(item);
            pos_[item] = order_.begin();
            return;
        }
        if (size() >= capacity_ && !order_.empty())
        {
            int last = order_.back();
            order_.pop_back();
            pos_.erase(last);
        }
        if (capacity_ > 0)
        {
            order_.push_front(item);
            pos_[item] = order_.begin();
        }
    }

    // Remove and return the least recently accessed item.
    // Throw std::out_of_range if the cache is empty.
    int remove()
    {
        // TODO
        if (empty())
        {
            throw std::out_of_range("cache is empty");
        }
        int last = order_.back();
        order_.erase(pos_[last]);
        pos_.erase(last);
        return last;
    }

    // Print the items from most recent to least recent access.
    void print() const
    {
        // TODO
        for (auto it = order_.begin(); it != order_.end(); it++)
        {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }

    bool contains(int item) const
    {
        // TODO
        return (pos_.find(item) != pos_.end());
        // placeholder return value
    }

    int size() const
    {
        // TODO
        return pos_.size(); // placeholder return value
    }

    bool empty() const
    {
        // TODO
        return pos_.empty(); // placeholder return value
    }
};
