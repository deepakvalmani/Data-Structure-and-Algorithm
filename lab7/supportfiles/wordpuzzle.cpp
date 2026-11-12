// Lab 7, Part B: find every dictionary word in a grid of letters.
// Usage: wordpuzzle <dictionary_file> <grid_file>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include "HashTable.h"
#include "grid.h"
#include "stopwatch.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <dictionary_file> <grid_file>\n";
        return 1;
    }
    // argv[1] is the dictionary file, argv[2] is the grid file

    HashTable dict;
    std::ifstream fin(argv[1]);
    if (!fin.is_open()) {
        std::cerr << "Cannot read dictionary file " << argv[1] << "\n";
        return 1;
    }
    int maxLen = 0;   // longest word in the dictionary
    for (std::string word; std::getline(fin, word); ) {
        if (!word.empty() && word.back() == '\r')   // Windows line endings
            word.pop_back();
        if (word.size() < 3)
            continue;
        dict.insert(word);
        maxLen = std::max(maxLen, (int) word.size());
    }

    Grid grid = readInGrid(argv[2]);
    if (grid.empty()) {
        std::cerr << "Cannot read grid file " << argv[2] << "\n";
        return 1;
    }
    int rows = grid.size(), cols = grid[0].size();

    Stopwatch sw;   // time only the search, not the loading of the dictionary
    int found = 0;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            for (int dir = 0; dir < 8; dir++)
                for (int len = 3; len <= maxLen; len++) {
                    std::string s = getWordInGrid(grid, r, c, dir, len);
                    if ((int) s.size() < len)   // hit the edge, longer is impossible
                        break;
                    if (dict.contains(s)) {
                        std::cout << DIRECTION[dir] << "(" << r << ", " << c << "): " << s << "\n";
                        found++;
                    }
                }

    std::cout << found << " words found\n";
    std::cout << "Found all words in " << sw.elapsedTime() / 1000 << " seconds\n";
}