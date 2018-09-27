#include "Archer.h"
#include <string>
#include <iostream>
using namespace std;

int Archer::getDamage() {
	damage2 = speed;
	return damage2;
}
void Archer::reset() {
	hp = maxHP;
	speed = originalSpeed;
}
bool Archer::useAbility() {
	speed = speed + 1;
	return true;
}