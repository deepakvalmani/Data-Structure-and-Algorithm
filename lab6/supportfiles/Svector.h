#pragma once

#include <cmath>
#include <iostream>
#include <map>

// Sparse vector of doubles: only the nonzero entries are stored.
class Svector {
private:
    std::map<int, double> entries_;  // index -> nonzero value

public:
    // Set the i-th entry to x (if x == 0, remove the entry if it exists).
    void set(int i, double x) {
        
        if(x == 0) { entries_.erase(i); return; }
        entries_[i] = x;
        // TODO
    }

    // Return the i-th entry (0 if not present).
    double get(int i) const {
        // TODO
        auto it = entries_.find(i);
        if (it != entries_.end()) {
            return it->second;
        }
        return 0.0;
       
        // placeholder return value
    }

    // Dot product of this vector with that, in time proportional to the
    // total number of nonzero entries in both vectors.
    double dot(const Svector& that) const {
        // TODO
        double result = 0.0;
        const auto& smaller = (this->entries_.size() < that.entries_.size() ? this->entries_ : that.entries_);
        const auto& larger = (this->entries_.size() < that.entries_.size() ? that.entries_ : this->entries_);
            for (const auto& [key, val] : smaller) {
                auto it = larger.find(key);
                if (it != larger.end()) {
                    result += val * it->second;
                }
            }
        return result; // placeholder return value
    }

    // Euclidean norm.
    double norm() const {
        // TODO
        double result = 0.0;
        for (const auto& [key, val] : entries_) {
            result += val * val;
        }
        return std::sqrt(result); // placeholder return value
    }

    // Sum of this vector and that.
    Svector add(const Svector& that) const {
        // TODO
        Svector sum;
        sum.entries_ = this->entries_;
        for (const auto& [key, val] :that.entries_) {
            sum.entries_[key] += val;
            if (sum.entries_[key] == 0.0) { sum.entries_.erase(key); }
        }

          
        return sum; // placeholder return value
    }

    // Multiply this vector by alpha (scaling by 0 removes every entry).
    void scale(double alpha) {
        // TODO
        if (alpha == 0.0) {
            entries_.clear();
            return;
        }
        else {
            for ( auto& [key, val] : entries_) {
                val *= alpha;
            }
        }
        return;
    }

    // Print the nonzero entries as {(i1,x1), (i2,x2), ...}
    void print() const {
        // TODO
        std::cout << "{ ";
        for (const auto& [key, val] : entries_) {
            if (val != 0.0) {
                std::cout << " (" << key << ", " << val << ")";

            }
        }
        std::cout<< " }" << std::endl;
    }
};
