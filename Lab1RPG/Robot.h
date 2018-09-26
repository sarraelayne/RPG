#pragma once
#include "Fighter.h"
#include <string>
#include <iostream>
using namespace std;

class Robot: public Fighter {
public:
    Robot(string name, int hp, int strength, int speed, int magic):Fighter(name, hp, strength, speed, magic){};
    ~Robot(){};
    int getDamage();
    void reset();
    bool useAbility();
};