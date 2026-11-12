// Lab 8, Parts A and B: generate a random perfect maze, and find a way out of it.
// Usage: maze <n> [seed]

#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "graph.hpp"
#include "depthfirstsearch.hpp"

using std::vector;

class Maze
{
    int n;
    // Cell (x, y) for 1 <= x, y <= n; x is the column (west to east), y is the row (south to north).
    // Rows and columns 0 and n+1 are a border of cells that never get visited,
    // so that the cells at the edge of the maze need no special cases.
    vector<vector<bool>> north, east, south, west; // north[x][y] is true if there is a wall
                                                   // between (x, y) and (x, y+1), and so on
    vector<vector<bool>> visited;
    vector<vector<bool>> onPath; // the cells on the way out (Part B)
    std::mt19937 rng;

public:
    Maze(int n, unsigned int seed)
        : n(n),
          north(n + 2, vector<bool>(n + 2, true)), east(north), south(north), west(north),
          visited(n + 2, vector<bool>(n + 2, false)), onPath(visited),
          rng(seed) {}

    int size() const { return n; }

    // The vertex of cell (x, y) in the graph of the maze: 0, 1, ..., n*n - 1, row by row.
    int cell(int x, int y) const { return (y - 1) * n + (x - 1); }

    // Part A: knock down walls to make a random perfect maze, starting from (1, 1).
    void generate()
    {
        clearVisited();
        generate(1, 1);
    }

    // Part A: the graph of the maze, with an edge between two adjacent cells if there is no wall between them.
    Graph toGraph() const
    {
        Graph G(n * n);
        // TODO: add an edge for every passage (missing wall) between two cells of the maze;
        //       add each passage once, not twice

        for (int y = 1; y <= n; y++)
        {
            for (int x = 1; x <= n; x++)
            {
                int current = (y - 1) * n + (x - 1);

                if (!east[x][y])
                {
                    int eastNeighbor = (y - 1) * n + x;
                    G.addEdge(current, eastNeighbor);
                }

                if (!north[x][y])
                {
                    int northNeighbor = y * n + (x - 1);
                    G.addEdge(current, northNeighbor);
                }
            }
        }

        return G;
    }

    // Part A: is there exactly one path between every pair of cells?
    // Hint: a graph is a tree if and only if it is connected and has V - 1 edges.
    bool isPerfect() const
    {
        // TODO: use toGraph() and DepthFirstSearch
        Graph G = toGraph();
        if (G.E() != G.V() - 1)
        {
            return false;
        }

        DepthFirstSearch dfs(G, 0);

        for (int v = 0; v < G.V(); v++)
        {
            if (!dfs.isConnected(v))
            {
                return false;
            }
        }

        return true;
    }

    // Part B: find a path from (1, 1) to (n, n), and mark its cells in onPath.
    // Return true if there is one.
    bool solve()
    {
        clearVisited();
        for (auto &col : onPath)
            col.assign(n + 2, false);
        return explore(1, 1);
    }

    bool isOnPath(int x, int y) const { return onPath[x][y]; }

    // Print the maze, with a * in each cell on the path. Row n (north) comes first.
    void print(std::ostream &out) const
    {
        for (int y = n; y >= 1; y--)
        {
            for (int x = 1; x <= n; x++)
                out << (north[x][y] ? "+---" : "+   ");
            out << "+\n";
            for (int x = 1; x <= n; x++)
                out << (west[x][y] ? "|" : " ") << (onPath[x][y] ? " * " : "   ");
            out << (east[n][y] ? "|" : " ") << "\n";
        }
        for (int x = 1; x <= n; x++)
            out << (south[x][1] ? "+---" : "+   ");
        out << "+\n";
    }

private:
    // A random integer in [0, k).
    int random(int k) { return rng() % k; }

    // Mark the interior cells unvisited, and the border cells visited.
    void clearVisited()
    {
        for (int x = 0; x <= n + 1; x++)
            for (int y = 0; y <= n + 1; y++)
                visited[x][y] = (x == 0 || y == 0 || x == n + 1 || y == n + 1);
    }

    // Part A: visit cell (x, y), and knock down walls to every cell that can be reached from it.
    void generate(int x, int y)
    {
        visited[x][y] = true;
        while (true)
        {

            // TODO: repeatedly
            //   - list the unvisited neighbors of (x, y), in the order N, E, S, W;
            //   - if there are none, return (go back to the previous cell);
            //   - pick the neighbor with index random(k) in the list, where k is its length;
            //   - knock down the wall between (x, y) and that neighbor (on both sides!),
            //     and visit the neighbor recursively.
            vector<std::pair<int, int>> neighbors;
            if (!visited[x][y + 1])
            {
                neighbors.push_back({x, y + 1});
            }
            if (!visited[x + 1][y])
            {
                neighbors.push_back({x + 1, y});
            }
            if (!visited[x][y - 1])
            {
                neighbors.push_back({x, y - 1});
            }
            if (!visited[x - 1][y])
            {
                neighbors.push_back({x - 1, y});
            }

            if (neighbors.empty())
            {
                return;
            }
            int k = neighbors.size();
            int index = random(k);
            int nx = neighbors[index].first;
            int ny = neighbors[index].second;
            if (nx == x + 1 && ny == y)
            {
                east[x][y] = false;
                west[nx][ny] = false;
            }
            if (nx == x && ny == y + 1)
            {
                north[x][y] = false;
                south[nx][ny] = false;
            }
            if (nx == x - 1 && ny == y)
            {
                west[x][y] = false;
                east[nx][ny] = false;
            }
            if (nx == x && ny == y - 1)
            {
                south[x][y] = false;
                north[nx][ny] = false;
            }
            generate(nx, ny);
        }
    }

    // Part B: explore from cell (x, y). If (n, n) can be reached, mark the cells
    // on the way from (x, y) to (n, n) in onPath, and return true.
    bool explore(int x, int y)
    {
        visited[x][y] = true;
        // TODO: see the pseudocode in the handout

        if (x == n && y == n)
        {
            onPath[x][y] = true;
            return true;
        }

        // North
        if (!north[x][y] && !visited[x][y + 1])
        {
            if (explore(x, y + 1))
            {
                onPath[x][y] = true;
                return true;
            }
        }

        // East
        if (!east[x][y] && !visited[x + 1][y])
        {
            if (explore(x + 1, y))
            {
                onPath[x][y] = true;
                return true;
            }
        }

        // South
        if (!south[x][y] && !visited[x][y - 1])
        {
            if (explore(x, y - 1))
            {
                onPath[x][y] = true;
                return true;
            }
        }

        // West
        if (!west[x][y] && !visited[x - 1][y])
        {
            if (explore(x - 1, y))
            {
                onPath[x][y] = true;
                return true;
            }
        }

        return false;
    }
};

int main(int argc, char *argv[])
{
    if (argc != 2 && argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <n> [seed]\n";
        return 1;
    }
    int n = std::stoi(argv[1]);
    unsigned int seed = argc == 3 ? std::stoul(argv[2]) : std::random_device{}();
    if (n < 1)
    {
        std::cerr << "n must be positive\n";
        return 1;
    }

    Maze maze(n, seed);
    maze.generate();
    Graph G = maze.toGraph();
    std::cout << n << "-by-" << n << " maze (seed " << seed << "): "
              << G.E() << " passages, " << (maze.isPerfect() ? "perfect" : "NOT perfect") << "\n";

    bool solved = maze.solve();
    maze.print(std::cout);
    if (!solved)
    {
        std::cout << "no way out\n";
        return 0;
    }

    // Cross-check: in a perfect maze, there is only one path, so
    // DepthFirstSearch must find the same one as explore().
    DepthFirstSearch dfs(G, maze.cell(1, 1));
    vector<int> path = dfs.pathTo(maze.cell(n, n));
    int marked = 0;
    for (int x = 1; x <= n; x++)
        for (int y = 1; y <= n; y++)
            marked += maze.isOnPath(x, y);
    bool same = (int)path.size() == marked;
    for (int v : path)
        same = same && maze.isOnPath(v % n + 1, v / n + 1);
    std::cout << "way out: " << marked << " cells; DepthFirstSearch "
              << (same ? "agrees" : "DISAGREES") << "\n";
}
