#pragma once

#include <vector>

// HexBoard: an n-by-n Hex board driven by a Union-Find data type.
//
// The board is a rhombus of n x n hexagonal cells. Player 0 (Red) tries to
// connect the TOP side to the BOTTOM side; player 1 (Blue) tries to connect
// the LEFT side to the RIGHT side.
//
// We model the two "sides to connect" as two extra virtual nodes per player:
//   - Red:   TOP    = n*n,     BOTTOM = n*n + 1
//   - Blue:  LEFT   = n*n + 2, RIGHT  = n*n + 3
// A stone placed on the top/bottom row is unioned with TOP/BOTTOM; a stone on
// the left/right column is unioned with LEFT/RIGHT. Every stone is unioned
// with its already-placed same-color neighbors. A player wins when their two
// virtual boundary nodes become connected through their stones.
//
// The UF type must support find(i) and unify(p,q).
template <typename UF>
class HexBoard
{
private:
    const int n_;
    std::vector<std::vector<int>> board_; // -1 empty, 0 Red, 1 Blue
    UF uf_;

    const int top_, bottom_, left_, right_;

    // Linear index of cell (r, c); 0 <= r, c < n_.
    int id(int r, int c) const
    {
        return r * n_ + c;
    }

    // True iff the two virtual boundary nodes of `player` are connected.
    bool connected(int a, int b)
    {
        return uf_.find(a) == uf_.find(b);
    }

    // The six axial neighbors of a hex cell on the rhombus board.
    static const std::vector<std::pair<int, int>> &dirs()
    {
        static const std::vector<std::pair<int, int>> kDirs = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, 1}, {1, -1}};
        return kDirs;
    }

public:
    HexBoard(int n) : n_(n),
                      board_(n, std::vector<int>(n, -1)),
                      uf_(n * n + 4),
                      top_(n * n),
                      bottom_(n * n + 1),
                      left_(n * n + 2),
                      right_(n * n + 3) {}

    int n() const { return n_; }

    // Value of a cell: -1 empty, 0 Red, 1 Blue.
    int cell(int r, int c) const { return board_[r][c]; }

    // Place a stone of `player` (0 or 1) at (r, c).
    // Returns true if this move completes a winning path for `player`.
    bool place(int r, int c, int player)
    {
        // TODO: board_[r][c] must be empty; mark it with `player`.
        // TODO: union (r, c) with every in-bounds same-color neighbor.
        // TODO: if player == 0, union with top_ when r == 0 and with
        //       bottom_ when r == n_ - 1.
        // TODO: if player == 1, union with left_ when c == 0 and with
        //       right_ when c == n_ - 1.
        // TODO: return true iff the two virtual boundary nodes of `player`
        //       are now connected.
        if (board_[r][c] != -1)
        {
            return false;
        }
        board_[r][c] = player;
        int current = id(r, c);

        for (auto [dr, dc] : dirs())
        {
            int nr = r + dr;
            int nc = c + dc;
            if (nr < n_ && nr >= 0 && nc < n_ && nc >= 0)
            {
                if (board_[nr][nc] == player)
                {
                    uf_.unify(current, id(nr,nc));
                }
            }
        }

        if (player == 0)
        {
            if (r == 0)
            {
                uf_.unify(top_, current);
            }
            if (r == n_ - 1)
            {
                uf_.unify(bottom_, current);
            }
            return connected(top_, bottom_);
        }
        if (player == 1)
        {
            if (c == 0)
            {
                uf_.unify(left_, current);
            }
            if (c == n_ - 1)
            {
                uf_.unify(right_, current);
            }
            return connected(left_, right_);
        }
        return false;
    }

    // True iff `player` currently has a winning path between their sides.
    bool isWinner(int player)
    {
        if (player == 0)
            return connected(top_, bottom_);
        return connected(left_, right_);
    }

    // True iff every cell of the board is occupied (board is full).
    bool isFull() const
    {
        for (int r = 0; r < n_; r++)
            for (int c = 0; c < n_; c++)
                if (board_[r][c] == -1)
                    return false;
        return true;
    }
};
