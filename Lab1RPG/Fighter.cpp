#include "Fighter.h"
using namespace std;

Fighter::Fighter(string inName, int inHP, int inStrength, int inSpeed, int inMagic) {
    name = inName;
    speed = inSpeed;
    originalSpeed = inSpeed;
    strength = inStrength;
    hp = inHP;
    magic = inMagic;
    maxHP = inHP;
    mana = inMagic * 5;
    maxMana = inMagic * 5;
    current_energy = inMagic * 2;
    maximum_energy = inMagic * 2;
}
Fighter::~Fighter() {
	cout << "in Fighter default";
}
string Fighter::getName() const {
	return name;
}
int Fighter::getMaximumHP() const {
	return maxHP;
}

int Fighter::getCurrentHP() const {
	return hp;
}

int Fighter::getStrength() const {
	return strength;
}

int Fighter::getSpeed() const {
	return speed;
}

int Fighter::getMagic() const {
	return magic;
}

void Fighter::takeDamage(int damage) {
	double speed_double;
	speed_double = speed/4;
	damage = damage - speed_double;
	if (damage < 1) {
		damage = 1;
	}
	hp = hp - damage;
}
void Fighter::regenerate() {
	int regenerate;
	regenerate = strength / 6;
	if (regenerate < 1) {
		regenerate = 1;
	}
	hp = hp + regenerate;
	if (hp > maxHP) {
		hp = maxHP;
	}
}