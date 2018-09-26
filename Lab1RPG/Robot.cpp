#include "Robot.h"
#include <string>
#include <iostream>
#include <cmath>
using namespace std;

int Robot::getDamage() {
    damage = strength + bonus_damage;
    bonus_damage = 0;
    return damage;
}
void Robot::reset() {
    hp = maxHP;
    current_energy = maximum_energy;
    bonus_damage = 0;
}
bool Robot::useAbility() {
    double bonus_damage_double;
    double powerMult;
    double const POWER = 4.0;
    bonus_damage = 0;
    if (current_energy >= ROBOT_ABILITY_COST) {
        powerMult = current_energy/(double)maximum_energy;
        bonus_damage_double = strength  * (pow(powerMult, POWER));
        current_energy = current_energy - ROBOT_ABILITY_COST;
        bonus_damage = bonus_damage_double + 0.5;
        return true;
    }
    else {
        return false;
    }
}