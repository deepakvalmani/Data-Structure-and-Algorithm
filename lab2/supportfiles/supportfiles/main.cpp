#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

#include "union-find.hpp"
#include "quick-find.hpp"
#include "quick-union.hpp"
#include "hex-board.hpp"
#include "stopwatch.hpp"

// ---------------------------------------------------------------------------
// Play a game: place up to numMoves random stones on an n-by-n board.
// A move that lands on an already-occupied cell is skipped. Returns the
// winner (-1 = nobody, 0 = Red, 1 = Blue). Using a fixed seed makes the
// random stream identical for every backend, so the comparison is fair.
// ---------------------------------------------------------------------------
template <typename UF>
int playGame(int n, int numMoves, unsigned int seed) {
    HexBoard<UF> board(n);
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> cellDist(0, n - 1);
    std::uniform_int_distribution<int> playerDist(0, 1);

    int winner = -1;
    for (int i = 0; i < numMoves; i++) {
        int r = cellDist(rng);
        int c = cellDist(rng);
        int player = playerDist(rng);
        if (board.cell(r, c) != -1) continue;   // occupied
        if (board.place(r, c, player)) {
            winner = player;
            break;                               // game over, someone won
        }
    }
    return winner;
}

// ---------------------------------------------------------------------------
// Part C: the No-Draw Theorem.
// Fill the board completely with random stones and check that EXACTLY ONE
// player has a winning path. Repeat over many trials.
// ---------------------------------------------------------------------------
template <typename UF>
bool verifyNoDraw(int n, unsigned int seed) {
    HexBoard<UF> board(n);
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> playerDist(0, 1);

    // Fill every cell in a random order.
    std::vector<std::pair<int, int>> cells;
    cells.reserve(n * n);
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            cells.emplace_back(r, c);
    std::shuffle(cells.begin(), cells.end(), rng);

    for (auto [r, c] : cells)
        board.place(r, c, playerDist(rng));

    bool redWins  = board.isWinner(0);
    bool blueWins = board.isWinner(1);
    return redWins != blueWins;   // exactly one of the two holds
}

// ---------------------------------------------------------------------------
// Part D: performance. Time the same random move sequence on each backend.
// ---------------------------------------------------------------------------
template <typename UF>
double timeGame(int n, int numMoves, unsigned int seed) {
    Stopwatch sw;
    int winner = playGame<UF>(n, numMoves, seed);
    double t = sw.elapsedTime();
    std::cout << "  winner = " << winner
              << "   time = " << t << " s\n";
    return t;
}

int main() {
    std::cout << "=== Part C: The No-Draw Theorem ===\n";
    const int kNoDrawN = 11;               // traditional 11x11 board
    const int kTrials  = 200;
    int violations = 0;
    for (int t = 0; t < kTrials; t++) {
        if (!verifyNoDraw<UF>(kNoDrawN, 1000 + t))
            violations++;
    }
    std::cout << "Board " << kNoDrawN << "x" << kNoDrawN
              << ", " << kTrials << " fully-filled trials.\n";
    std::cout << "Violations (both or neither player wins): " << violations << "\n";
    std::cout << (violations == 0
                      ? "No-Draw Theorem holds in all trials.\n"
                      : "No-Draw Theorem FAILED!\n");

    std::cout << "\n=== Part D: Performance (same random sequence per backend) ===\n";
    const int kPerfN     = 250;             // large board: O(n) QuickFind shows
    const int kNumMoves  = 50000;            // clearly, WQU stays near O(1)/move
    const unsigned int kSeed = 4242;

    std::cout << "Board " << kPerfN << "x" << kPerfN << ", " << kNumMoves << " moves.\n";
    std::cout << "[QuickFind]   "; timeGame<QuickFindUF>(kPerfN, kNumMoves, kSeed);
    std::cout << "[QuickUnion]  "; timeGame<QuickUnionUF>(kPerfN, kNumMoves, kSeed);
    std::cout << "[WeightedQU]  "; timeGame<UF>(kPerfN, kNumMoves, kSeed);

    return 0;
}