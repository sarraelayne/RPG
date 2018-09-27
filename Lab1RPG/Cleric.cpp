#include "Cleric.h"
#include <string>
#include <iostream>
using namespace std;

int Cleric::getDamage() {
	damage2 = magic;
	return damage2;
}
void Cleric::reset() {
	hp = maxHP;
	mana = maxMana;
}
void Cleric::regenerate() {
	Fighter::regenerate();
	int manaRegen;
	
	manaRegen = magic / 5;
	if (manaRegen < 1) {
		manaRegen = 1;
	}
	mana = mana + manaRegen;
	if (mana > maxMana) {
		mana = maxMana;
	}
}
bool Cleric::useAbility() {
	int tempHP;
	if (mana >= CLERIC_ABILITY_COST) {
		tempHP = hp + magic/3;
		if (tempHP < 1) {
			tempHP = 1;
		}
		hp = tempHP;
		if (hp > maxHP) {
			hp = maxHP;
		}
		mana = mana - CLERIC_ABILITY_COST;
		return true;
	}
	else {
		return false;
	}
}