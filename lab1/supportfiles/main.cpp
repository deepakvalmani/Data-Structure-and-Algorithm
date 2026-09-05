#include <iostream>
#include <random>
#include <string>
#include "text-buffer.hpp"
#include "stopwatch.hpp"

// Perform random operations on a text buffer.
// numOps: number of operations to perform.
// opDistribution: 0 = insert, 1 = moveLeft, 2 = moveRight, 3 = remove.
// Default probabilities: 40% insert, 20% left, 20% right, 20% remove.
template <typename TextBuffer>
void randomOps(TextBuffer& buf, int numOps, unsigned int seed = 0) {
    std::mt19937 rng(seed != 0 ? seed : std::random_device{}());
    std::uniform_int_distribution<int> opDist(0, 99); // 0-99
    std::uniform_int_distribution<char> charDist('a', 'z');

    for (int i = 0; i < numOps; ++i) {
        int r = opDist(rng);
        if (r < 40) {                // 40% insert
            char c = charDist(rng);
            buf.insert(c);
        } else if (r < 60) {         // 20% move left
            buf.moveLeft();
        } else if (r < 80) {         // 20% move right
            buf.moveRight();
        } else {                     // 20% remove
            buf.remove();
        }
    }
}

// Helper to measure time of random operations.
template <typename TextBuffer>
double measureTime(TextBuffer& buf, int numOps, unsigned int seed = 0) {
    Stopwatch sw;
    randomOps(buf, numOps, seed);
    return sw.elapsedTime();
}

int main() {
    const int NUM_OPS = 100000;          // number of operations per test
    const unsigned int SEED = 12345;     // fixed seed for reproducibility

    // Test Array-based buffer
    TextBufferArray arrBuf;
    double arrTime = measureTime(arrBuf, NUM_OPS, SEED);
    std::cout << "Array-based buffer time: " << arrTime << " seconds\n";

    // Test List-based buffer
    TextBufferList listBuf;
    double listTime = measureTime(listBuf, NUM_OPS, SEED);
    std::cout << "List-based buffer time:  " << listTime << " seconds\n";

    // Optional: verify that both buffers have the same text content
    // (they should, because they received identical random operations with same seed)
    // We can getText() and compare lengths or contents.
    std::string textArr = arrBuf.getText();
    std::string textList = listBuf.getText();
    bool same = (textArr == textList);
    std::cout << "Texts are " << (same ? "identical" : "different")
              << " (lengths: " << textArr.size() << " vs " << textList.size() << ")\n";

    // Also show a snippet of the text
    std::cout << "Final text (first 100 chars):\n";
    std::cout << textArr.substr(0, 100) << "\n";

    return 0;
}
