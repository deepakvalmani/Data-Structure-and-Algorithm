#pragma once

#include <chrono>

/**
 * A high-precision stopwatch class for measuring elapsed time.
 *
 * Uses std::chrono::high_resolution_clock for maximum precision timing.
 * Elapsed time is returned as a double in milliseconds, preserving
 * sub-millisecond precision through floating-point arithmetic.
 */
class Stopwatch {
public:
    // Constructs a Stopwatch and starts timing immediately.
    Stopwatch() : start {std::chrono::high_resolution_clock::now()} { }

    // Resets the stopwatch to the current time.
    void reset() {
        start = std::chrono::high_resolution_clock::now();
    }

    //Gets the elapsed time since construction or last reset.
    double elapsedTime() const {
        const auto now = std::chrono::high_resolution_clock::now();

        // Compute difference as floating-point milliseconds
        const std::chrono::duration<double, std::milli> duration = now - start;

        // Return as double
        return duration.count();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;  // Start the stopwatch
};
