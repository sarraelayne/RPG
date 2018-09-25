#include "Fighter.h"
using namespace std;

Fighter::Fighter(string inName, int inHP, int inStrength, int inSpeed, int inMagic) {
    cout << "Fighter constructor";
    name = inName;
    speed = inSpeed;
    strength = inStrength;
    hp = inHP;
    magic = inMagic;
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

int Fighter::getDamage() {
	return damage;
}
void Fighter::takeDamage(int damage) {
	damage = damage - (0.25 * speed);
}
void Fighter::regenerate() {
	hp = hp + strength/6;
}