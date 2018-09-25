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
	damage = damage - (0.25 * speed);
	hp = hp - damage;
}
void Fighter::regenerate() {
	hp = hp + strength/6;
}