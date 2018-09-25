#include "Archer.h"
#include <string>
#include <iostream>
using namespace std;

int Archer::getDamage() {
	damage = speed;
	return damage;
}
void Archer::reset() {
	hp = maxHP;
	speed = originalSpeed;
}
bool Archer::useAbility() {
	speed = speed + 1;
	return true;
}