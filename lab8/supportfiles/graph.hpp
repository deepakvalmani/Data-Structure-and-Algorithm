#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <forward_list>
#include <stdexcept>

class Graph {
    std::vector<std::forward_list<int>> _adj;
    std::vector<int> _degree;
    int _E;

public:
    Graph(int n) : _adj(n), _degree(n), _E{0} {}

    Graph(std::istream& in) : _E{0} {
        int V, E;
        if (!(in >> V >> E))
            throw std::invalid_argument("could not read the number of vertices and edges");
        if (V < 0 || E < 0)
            throw std::invalid_argument("number of vertices and edges in a Graph must be non-negative");
        _adj.resize(V);
        _degree.resize(V);
        for (int i = 0; i < E; i++) {
            int v, w;
            if (!(in >> v >> w))
                throw std::invalid_argument("could not read edge " + std::to_string(i + 1) + " of " + std::to_string(E));
            validateVertex(v);
            validateVertex(w);
            addEdge(v, w);
        }
    }

    int V() const {
        return _adj.size();
    }
    int E() const {
        return _E;
    }

    void addEdge(int v, int w) {
        validateVertex(v);
        validateVertex(w);
        _adj[v].push_front(w);
        _adj[w].push_front(v);
        _degree[v]++;
        _degree[w]++;
        _E++;
    }

    const std::forward_list<int>& adj(int v) const {
        validateVertex(v);
        return _adj[v];
    }

    int degree(int v) const {
        validateVertex(v);
        return _degree[v];
    }

    std::string to_string() const {
        std::string s; 
        s.append(std::to_string(V()) + " vertices, " + std::to_string(_E) + " edges " + "\n");
        for (int v = 0; v < V(); v++) {
            s.append(std::to_string(v) + ": ");
            for (int w : _adj[v]) {
                s.append(std::to_string(w) + " ");
            }
            s.append("\n");
        }
        return s;
    }

private:
    void validateVertex(int v) const {
        if (v < 0 || v >= V())
            throw std::invalid_argument("vertex " + std::to_string(v) + " is not between 0 and " + std::to_string((V()-1)));
    }

};


