#ifndef FORDFULKERSON_H
#define FORDFULKERSON_H

#include "FlowNetwork.h"
#include <vector>
#include <limits>
#include <iostream>
using namespace std;

class FordFulkerson {
private:
    FlowNetwork& network;
    vector<bool> visited;
    vector<pair<int, size_t>> parent;
    
    bool dfs(int u, int sink) {
        if (u == sink) return true;
        visited[u] = true;
        
        const auto& edges = network.getEdges(u);
        for (size_t i = 0; i < edges.size(); i++) {
            const Edge& e = edges[i];
            if (!visited[e.to] && e.residualCapacity() > 0) {
                parent[e.to] = {u, i};
                if (dfs(e.to, sink)) return true;
            }
        }
        return false;
    }
    
public:
    FordFulkerson(FlowNetwork& net) : network(net) {}
    
    int maxFlow(int source, int sink) {
        int totalFlow = 0;
        int iteration = 0;
        
        cout << "\n=== FORD-FULKERSON ALGORITHM (DFS) ===\n";
        
        while (true) {
            visited.assign(network.getNumVertices(), false);
            parent.assign(network.getNumVertices(), {-1, 0});
            
            if (!dfs(source, sink)) break;
            
            // Find bottleneck (minimum residual capacity along the path)
            int bottleneck = numeric_limits<int>::max();
            int v = sink;
            while (v != source) {
                int u = parent[v].first;
                size_t edgeIdx = parent[v].second;
                const Edge& e = network.getEdges(u)[edgeIdx];
                bottleneck = min(bottleneck, e.residualCapacity());
                v = u;
            }
            
            // Update flows along the path
            v = sink;
            while (v != source) {
                int u = parent[v].first;
                size_t edgeIdx = parent[v].second;
                Edge& e = network.getEdge(u, edgeIdx);
                e.addFlow(bottleneck);
                Edge& rev = network.getEdge(e.to, e.rev);
                rev.addFlow(-bottleneck);
                v = u;
            }
            
            totalFlow += bottleneck;
            iteration++;
            cout << "  Iteration " << iteration << ": +" << bottleneck 
                 << " (total = " << totalFlow << ")\n";
        }
        
        cout << "  Total iterations: " << iteration << endl;
        cout << "  Max flow = " << totalFlow << endl;
        return totalFlow;
    }
};

#endif