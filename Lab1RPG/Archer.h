#ifndef ARCHER_H
#define ARCHER_H
#include "Fighter.h"
using namespace std;

class Archer: public Fighter {
public:
    Archer(string name, int hp, int strength, int speed, int magic):Fighter(name, hp, strength, speed, magic){};
    ~Archer(){};
    int getDamage();
    void reset();
    bool useAbility();
};

#endif 