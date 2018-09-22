#include "Archer.h"

Archer::Archer() {
    cout << "default archer constructor";
}

Archer::Archer(int fighterNum) {
    cout << "archer(fighterNum) constructor";
    srand(time(NULL));
    //setMe(fighterNum);
}

Archer::~Archer() {
    cout << "archer destructor";
}

int Archer::selectAction(int game [3][3]) {ame, action)) {
        action = rand % 9;
    }
}