#pragma once
#include <set>

using namespace std;

class node {
    public:
    set<int> neighbors;
    bool beenThere;
    int pos;
    
    node();
    void addNode(int nbr);
};