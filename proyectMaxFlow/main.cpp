#include "FordFulkerson.h"
#include "EdmondsKarp.h"
#include <iostream>
using namespace std;

void testSimple() {
    cout << "\n" << string(50, '=') << endl;
    cout << "TEST 1: Simple network (3 vertices)" << endl;
    cout << string(50, '=') << endl;
    
    FlowNetwork net(3);
    net.addEdge(0, 1, 5);
    net.addEdge(1, 2, 3);
    net.print();
    
    FordFulkerson ff(net);
    int flowFF = ff.maxFlow(0, 2);
    
    net.resetFlows();
    
    EdmondsKarp ek(net);
    int flowEK = ek.maxFlow(0, 2);
    
    cout << "\n--- RESULT ---" << endl;
    cout << "Ford-Fulkerson: " << flowFF << endl;
    cout << "Edmonds-Karp:   " << flowEK << endl;
    cout << "Expected flow: 3" << endl;
}

void testTwoPaths() {
    cout << "\n" << string(50, '=') << endl;
    cout << "TEST 2: Network with two independent paths" << endl;
    cout << string(50, '=') << endl;
    
    FlowNetwork net(4);
    net.addEdge(0, 1, 3);
    net.addEdge(0, 2, 3);
    net.addEdge(1, 3, 3);
    net.addEdge(2, 3, 3);
    net.print();
    
    FordFulkerson ff(net);
    int flowFF = ff.maxFlow(0, 3);
    
    net.resetFlows();
    
    EdmondsKarp ek(net);
    int flowEK = ek.maxFlow(0, 3);
    
    cout << "\n--- RESULT ---" << endl;
    cout << "Ford-Fulkerson: " << flowFF << endl;
    cout << "Edmonds-Karp:   " << flowEK << endl;
    cout << "Expected flow: 6" << endl;
}

void testClassic() {
    cout << "\n" << string(50, '=') << endl;
    cout << "TEST 3: Classic network (CLRS)" << endl;
    cout << string(50, '=') << endl;
    
    FlowNetwork net(6);
    net.addEdge(0, 1, 16);
    net.addEdge(0, 2, 13);
    net.addEdge(1, 2, 10);
    net.addEdge(1, 3, 12);
    net.addEdge(2, 1, 4);
    net.addEdge(2, 4, 14);
    net.addEdge(3, 2, 9);
    net.addEdge(3, 5, 20);
    net.addEdge(4, 3, 7);
    net.addEdge(4, 5, 4);
    net.print();
    
    FordFulkerson ff(net);
    int flowFF = ff.maxFlow(0, 5);
    
    net.resetFlows();
    
    EdmondsKarp ek(net);
    int flowEK = ek.maxFlow(0, 5);
    
    cout << "\n--- RESULT ---" << endl;
    cout << "Ford-Fulkerson: " << flowFF << endl;
    cout << "Edmonds-Karp:   " << flowEK << endl;
}

int main() {
    cout << "========================================" << endl;
    cout << "   MAXIMUM FLOW ALGORITHMS" << endl;
    cout << "   Ford-Fulkerson vs Edmonds-Karp" << endl;
    cout << "========================================" << endl;
    
    testSimple();
    testTwoPaths();
    testClassic();
    
    cout << "\n========================================" << endl;
    cout << "ALL TESTS COMPLETED" << endl;
    cout << "========================================" << endl;
    
    return 0;
}