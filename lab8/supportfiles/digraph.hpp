#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <forward_list>
#include <stdexcept>

class Digraph {
    std::vector<std::forward_list<int>> _adj;
    std::vector<int> _indegree;
    std::vector<int> _outdegree;
    int _E;

public:
    Digraph(int n) : _adj(n), _indegree(n), _outdegree(n), _E{0} {}

    Digraph(std::istream& in) : _E{0} {
        int V, E;
        if (!(in >> V >> E))
            throw std::invalid_argument("could not read the number of vertices and edges");
        if (V < 0 || E < 0)
            throw std::invalid_argument("number of vertices and edges in a Digraph must be non-negative");
        _adj.resize(V);
        _indegree.resize(V);
        _outdegree.resize(V);
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
        _outdegree[v]++;
        _indegree[w]++;
        _E++;
    }

    const std::forward_list<int>& adj(int v) const {
        validateVertex(v);
        return _adj[v];
    }

    int indegree(int v) const {
        validateVertex(v);
        return _indegree[v];
    }

    int outdegree(int v) const {
        validateVertex(v);
        return _outdegree[v];
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

    Digraph reverse() const {
        Digraph r(V());
        for(int v=0; v<V(); v++) {
            for(int w : adj(v)) {
                r.addEdge(w,v);
            }
        }
        return r;
    }

private:
    void validateVertex(int v) const {
        if (v < 0 || v >= V())
            throw std::invalid_argument("vertex " + std::to_string(v) + " is not between 0 and " + std::to_string((V()-1)));
    }

};


