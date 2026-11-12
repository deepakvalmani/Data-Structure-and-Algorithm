// Lab 8, Part C: test client for DirectedCycle.
// Reads a digraph from a file, and prints a directed cycle in it, if there is one.
// Usage: cycle <digraph_file>

#include <fstream>
#include <iostream>
#include <vector>
#include "digraph.hpp"
#include "directed-cycle.hpp"

// Is c = c[0] c[1] ... c[k] a directed cycle of G, i.e., c[0] == c[k], k >= 1,
// every c[i] -> c[i+1] is an edge of G, and c[0], ..., c[k-1] are distinct?
bool isDirectedCycle(const Digraph& G, const std::vector<int>& c) {
    if (c.size() < 2 || c.front() != c.back()) return false;
    std::vector<bool> seen(G.V(), false);
    for (size_t i = 0; i + 1 < c.size(); i++) {
        int v = c[i], w = c[i + 1];
        if (v < 0 || v >= G.V() || seen[v]) return false;
        seen[v] = true;
        bool edge = false;
        for (int x : G.adj(v))
            edge = edge || x == w;
        if (!edge) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <digraph_file>\n";
        return 1;
    }
    std::ifstream in(argv[1]);
    if (!in) {
        std::cerr << "Cannot open " << argv[1] << "\n";
        return 1;
    }
    Digraph G(in);
    std::cout << G.V() << " vertices, " << G.E() << " edges\n";

    DirectedCycle finder(G);
    if (!finder.hasCycle()) {
        std::cout << "no directed cycle\n";
        return 0;
    }
    std::cout << "directed cycle:";
    for (int v : finder.cycle())
        std::cout << " " << v;
    std::cout << "\n";
    if (!isDirectedCycle(G, finder.cycle()))
        std::cout << "ERROR: this is not a directed cycle of the digraph\n";
}
