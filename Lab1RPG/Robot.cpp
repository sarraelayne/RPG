#include "Robot.h"
#include <string>
#include <iostream>
#include <cmath>
using namespace std;

int Robot::getDamage() {
    cout << "bonus_damage getDamage: " << bonus_damage << endl;
    damage = strength + bonus_damage;
    return damage;
}
void Robot::reset() {
    hp = maxHP;
    current_energy = magic * 2;
    bonus_damage = 0;
}
bool Robot::useAbility() {
    double bonus_damage_double;
    double powerMult;
    double power;
    if (current_energy >= ROBOT_ABILITY_COST) {
        powerMult = current_energy/(double)maximum_energy;
        power = 4.0;
        bonus_damage_double = strength  * (pow(powerMult, power));
        energy = current_energy - ROBOT_ABILITY_COST;
        bonus_damage = bonus_damage_double + 0.5;
        return true;
    }
    else {
        return false;
    }
}