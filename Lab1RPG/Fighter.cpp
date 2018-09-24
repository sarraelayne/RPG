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
	cout << "in Fighter default"
}
bool Fighter::isValidMove(int game[3][3]/*size of tictactoe board*/, int action) {
	if (game[action /3][action % 3] == -1) {
		return true;
	}
	return false;
}
string Fighter::getName() const = 0 {
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

int Robot::getDamage() {
	return damage;
}
void Fighter::takeDamage(int damage) = 0 {
		damage = damage - (0.25 * speed);
		return damage;
}
void Fighter::regenerate() = 0 {
	hp = hp + strength/6;
}