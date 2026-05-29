#ifndef FLOWNETWORK_H
#define FLOWNETWORK_H

#include "Edge.h"
#include <vector>
#include <iostream>
using namespace std;

class FlowNetwork {
private:
    int numVertices;
    vector<vector<Edge>> graph;
    
public:
    FlowNetwork(int n) : numVertices(n), graph(n) {}
    
    void addEdge(int from, int to, int capacity) {
        Edge fwd(to, capacity, graph[to].size());
        Edge rev(from, 0, graph[from].size());
        graph[from].push_back(fwd);
        graph[to].push_back(rev);
    }
    
    const vector<Edge>& getEdges(int v) const {
        return graph[v];
    }
    
    Edge& getEdge(int from, size_t index) {
        return graph[from][index];
    }
    
    int getNumVertices() const {
        return numVertices;
    }
    
    void resetFlows() {
        for (int i = 0; i < numVertices; i++) {
            for (auto& edge : graph[i]) {
                edge.flow = 0;
            }
        }
    }
    
    void print() const {
        cout << "Flow Network (" << numVertices << " vertices):\n";
        for (int i = 0; i < numVertices; i++) {
            for (const auto& e : graph[i]) {
                if (e.capacity > 0) {
                    cout << "  " << i << " -> " << e.to 
                         << " [cap=" << e.capacity 
                         << ", flow=" << e.flow << "]\n";
                }
            }
        }
    }
};

#endif