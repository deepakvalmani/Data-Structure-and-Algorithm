#pragma once

#include <chrono>

class Stopwatch {
public:
    Stopwatch() : start {std::chrono::high_resolution_clock::now()} {
    }
    void reset() {
        start = std::chrono::high_resolution_clock::now();
    }
    // elapsed time in milliseconds
    double elapsedTime() const {
        const auto now = std::chrono::high_resolution_clock::now();
        const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
        return duration.count();
    }
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
};
