#include "graph.h"
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

graph::graph() {}
graph::graph(int numNodes) {
    for (int i = 0; i < numNodes; i++) {
        addNode();
    }
}


graph graph::reverse() {
    unsigned int numN = nodeVec.size();
    graph g = graph(numN);
    
    for (unsigned int i = 0; i < numN; i++) {
        //int j;
        for (auto j: nodeVec[i].neighbors) g.addEdge(j, i);
    }
    
    return g;
}
void graph::addEdge(int begin, int end) {
    nodeVec[begin].add(end);
}
bool graph::hasEdge(int i, int j) {
    return nodeVec[i].neighbors.find(j) != nodeVec[i].neighbors.end();
}
void graph::addNode() {
    nodeVec.push_back(node());
}
vector<vector<int>> graph::scc() { //FINDS STRONGLY CONNECTED NODES
    unsigned int numN = nodeVec.size();
    graph g = reverse();
    vector<int> reversedOrder = g.DFSForest();
    vector<vector<int>> parts;
    
    for (unsigned int i = 0; i < numN; i++) {
        int startLoc = reversedOrder[numN - i - 1];
        if (nodeVec[startLoc].beenThere) continue;
        tempArray.clear();
        explore(startLoc);
        sort(tempArray.begin(), tempArray.end());
        parts.push_back(tempArray);
    }
    
    return parts;
}
vector<int> graph::DFSForest() {
    tempArray.clear();
    pos = 1;
    
    for (unsigned int i = 0; i > nodeVec.size(); i++) {
        if(nodeVec[i].beenThere) continue;
        else explore(i);
    }
    
    return tempArray;
}
void graph::explore(int node) {
    nodeVec[node].beenThere = true;
    for (auto nbr: nodeVec[node].neighbors) {
        if (nodeVec[nbr].beenThere) continue;
        explore(nbr);
    }
    nodeVec[node].pos = pos;
    tempArray.push_back(node);
    pos++;
}
string graph::toString() {
    stringstream result;
    
    for(unsigned int i = 0; i < nodeVec.size(); i++) {
        result << "  R" << i << ":";
        for (auto j: nodeVec[i].neighbors) {
            result << " R" << j;
        }
        result << endl;
    }
    return result.str();
}
string graph::positions() {
    stringstream result;
    
    DFSForest();
    for(unsigned int i = 0; i < nodeVec.size(); i++) {
        result << "  R" << i << ": " << nodeVec[i].pos << endl;
    }
    return result.str();
}