#include "Robot.h"
using namespace std;

int Robot::getDamage() {
    damage = strength;
    return damage;
}
void Robot::reset() {
    hp = maxHP;
    current_energy = magic * 2;
    bonus_damage = 0;
}
bool Robot::useAbility() {
    if (current_energy >= ROBOT_ABILITY_COST) {
        bonus_damage = strength  * ((current_energy/maximum_energy)^4);
        energy = current_energy - ROBOT_ABILITY_COST;
        return true;
    }
    else {
        return false;
    }
}