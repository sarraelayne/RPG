#pragma once
#include "Fighter.h"
using namespace std;

class Robot: public Fighter {
public:
    Robot(string name, int hp, int strength, int speed, int magic):Fighter(name, hp, strength, speed, magic){};
    ~Robot(){};
    int getDamage();
    void reset();
    bool useAbility();
protected:
    int damage;
    int energy;
    int bonus_damage;
    int current_energy;
    int maximum_energy;
};