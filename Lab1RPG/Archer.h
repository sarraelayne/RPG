#ifndef ARCHER_H
#define ARCHER_H
#include "Fighter.h"
using namespace std;

class Archer: public Fighter {
public:
    Archer();
    Archer(int fighterNum)
    ~Archer(){};
    int selectAction(int game[3][3]);
};

#endif 