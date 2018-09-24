#include "Cleric.h"
using namespace std;

int Cleric::getDamage() {
	damage = magic;
	return damage;
}
void Cleric::reset() {
	mana = magic * 5;
}
void Cleric::regenerate() {
	
}
bool Cleric::useAbility {
	if (mana >= CLERIC_ABILITY_COST) {
		hp = hp + magic/3;
		mana = mana - CLERIC_ABILITY_COST;
		return true;
	}
	else {
		return false;
	}
}