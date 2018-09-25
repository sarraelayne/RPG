#pragma once
#include "Fighter.h"
#include <string>
#include <iostream>
using namespace std;

class Cleric: public Fighter {
public:
    Cleric(string name, int hp, int strength, int speed, int magic):Fighter(name, hp, strength, speed, magic) {};
    ~Cleric(){};
    int getDamage();
    void reset();
    void regenerate();
    bool useAbility();
};
