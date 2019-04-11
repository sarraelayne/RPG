#pragma once
#include "node.h"
#include <vector>
#include <iostream>

using namespace std;

class graph {
public:
    int pos;
    vector<node> nodeVec;
    vector<int> tempArray;
    
    graph();
    graph(int numNodes);
    
    graph reverse();
    void addEdge(int begin, int end);
    bool hasEdge(int i, int j);
    void addNode();
    vector<vector<int>> scc();
    vector<int> DFSForest();
    void explore(int node);
    string toString();
    string positions();
};