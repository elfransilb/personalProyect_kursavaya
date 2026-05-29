#ifndef EDMONDSKARP_H
#define EDMONDSKARP_H

#include "FlowNetwork.h"
#include <vector>
#include <queue>
#include <limits>
#include <iostream>
using namespace std;

class EdmondsKarp {
private:
    FlowNetwork& network;
    vector<int> parent;
    vector<size_t> parentEdgeIdx;
    
    bool bfs(int source, int sink) {
        vector<bool> visited(network.getNumVertices(), false);
        parent.assign(network.getNumVertices(), -1);
        parentEdgeIdx.assign(network.getNumVertices(), 0);
        
        queue<int> q;
        q.push(source);
        visited[source] = true;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            const auto& edges = network.getEdges(u);
            for (size_t i = 0; i < edges.size(); i++) {
                const Edge& e = edges[i];
                if (!visited[e.to] && e.residualCapacity() > 0) {
                    visited[e.to] = true;
                    parent[e.to] = u;
                    parentEdgeIdx[e.to] = i;
                    if (e.to == sink) return true;
                    q.push(e.to);
                }
            }
        }
        return false;
    }
    
public:
    EdmondsKarp(FlowNetwork& net) : network(net) {}
    
    int maxFlow(int source, int sink) {
        int totalFlow = 0;
        int iteration = 0;
        
        cout << "\n=== EDMONDS-KARP ALGORITHM (BFS) ===\n";
        
        while (bfs(source, sink)) {
            // Find bottleneck
            int bottleneck = numeric_limits<int>::max();
            int v = sink;
            while (v != source) {
                int u = parent[v];
                size_t edgeIdx = parentEdgeIdx[v];
                const Edge& e = network.getEdges(u)[edgeIdx];
                bottleneck = min(bottleneck, e.residualCapacity());
                v = u;
            }
            
            // Update flows
            v = sink;
            while (v != source) {
                int u = parent[v];
                size_t edgeIdx = parentEdgeIdx[v];
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