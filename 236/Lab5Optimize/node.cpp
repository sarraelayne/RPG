#include "node.h"

node::node() {
    beenThere = false;
    pos = -1;
}

void node::addNode(int nbr) {
    neighbors.insert(nbr);
}