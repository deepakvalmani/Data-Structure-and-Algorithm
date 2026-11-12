#pragma once

#include <vector>
#include <algorithm>
#include "digraph.hpp"

// Lab 8, Part C: find a directed cycle in a digraph, if there is one.
class DirectedCycle
{
    std::vector<bool> marked;
    std::vector<int> edgeTo;
    std::vector<bool> onStack; // onStack[v]: is dfs(G, v) still running?
    std::vector<int> _cycle;   // a directed cycle w -> ... -> v -> w, as w ... v w (empty if none)

public:
    DirectedCycle(const Digraph &G) : marked(G.V(), false), edgeTo(G.V(), -1), onStack(G.V(), false)
    {
        // TODO: run dfs() from every unmarked vertex v = 0, 1, ..., V-1 (in this order),
        //       until a cycle is found

        for (int v = 0; v < G.V(); v++)
        {
            if (!marked[v] && _cycle.empty())
            {
                dfs(G, v);
            }
        }
    }

    bool hasCycle() const
    {
        return !_cycle.empty();
    }

    // The vertices of a directed cycle, with the first vertex repeated at the end; empty if there is none.
    const std::vector<int> &cycle() const
    {
        return _cycle;
    }

private:
    void dfs(const Digraph &G, int v)
    {
        marked[v] = true;
        onStack[v] = true;
        // TODO: for each w in G.adj(v):
        //   - if a cycle has already been found, return;
        //   - if w is unmarked, set edgeTo[w] = v and visit w recursively;
        //   - otherwise, if w is on the stack, the edge v -> w closes a cycle: store it in _cycle,
        //     as w ... v w (follow edgeTo[] from v back to w, then reverse, then add w again)
        for (int w : G.adj(v))
        {
            if (!_cycle.empty())
                break;

            if (!marked[w])
            {
                edgeTo[w] = v;
                dfs(G, w);
            }
            else if (onStack[w])
            {
                // Follow edgeTo backwards from v to w
                for (int x = v; x != w; x = edgeTo[x])
                {
                    _cycle.push_back(x);
                }

                _cycle.push_back(w);

                // Reverse to get the forward path
                std::reverse(_cycle.begin(), _cycle.end());

                // Close the cycle
                _cycle.push_back(w);
            }
        }

        onStack[v] = false;
    }
};
