#ifndef EDGE_H
#define EDGE_H

#include <cstddef>

struct Edge {
    int to;           // destination vertex
    int capacity;     // maximum capacity
    int flow;         // current flow
    size_t rev;       // index of reverse edge
    
    Edge(int t, int c, size_t r) : to(t), capacity(c), flow(0), rev(r) {}
    
    int residualCapacity() const {
        return capacity - flow;  // how much more can be sent
    }
    
    void addFlow(int f) {
        flow += f;
    }
};

#endif