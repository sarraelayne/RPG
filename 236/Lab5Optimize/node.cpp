#include "node.h"

node::node() {
    beenThere = false;
    pos = -1;
}

void node::add(int nbr) {
    neighbors.insert(nbr);
}