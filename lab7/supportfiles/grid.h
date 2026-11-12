#pragma once

// Reading a grid of letters, and retrieving a string from it in one of the
// 8 compass directions.
//
// Written by Aaron Bloomfield, 2009
// Updated by Imran Rauf, 2024, 2026

#include <fstream>
#include <string>
#include <vector>

using Grid = std::vector<std::vector<char>>;   // grid[r][c]; grid[0][0] is the upper-left letter

// Direction names, indexed by the direction numbers used by getWordInGrid().
const char* const DIRECTION[8] = {"N ", "NE", "E ", "SE", "S ", "SW", "W ", "NW"};

// Read a grid file: the number of rows, the number of columns, and then
// rows * cols letters. Return an empty grid if the file cannot be opened.
inline Grid readInGrid(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open())
        return Grid();

    int rows, cols;
    fin >> rows >> cols;
    Grid grid(rows, std::vector<char>(cols));
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            fin >> grid[r][c];
    return grid;
}

// Return the string of (at most) len letters that starts at (startRow, startCol)
// and goes in direction dir: 0 is north (upwards), 1 is north-east, and so on
// clockwise up to 7 for north-west. If the edge of the grid is reached first,
// the returned string is shorter than len.
inline std::string getWordInGrid(const Grid& grid, int startRow, int startCol, int dir, int len) {
    static const int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    static const int dc[8] = {0, 1, 1, 1, 0, -1, -1, -1};
    int numRows = grid.size(), numCols = grid[0].size();
    std::string output;
    for (int i = 0, r = startRow, c = startCol; i < len; i++, r += dr[dir], c += dc[dir]) {
        if (r < 0 || r >= numRows || c < 0 || c >= numCols)
            break;
        output += grid[r][c];
    }
    return output;
}
