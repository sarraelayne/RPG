#pragma once
#include "FighterInterface.h"
using namespace std;

class Fighter: public FighterInterface {
public:
    Fighter(string inName, int inHP, int inStrength, int inSpeed, int inMagic);
    ~Fighter();
    //virtual int selectAction(int game[3][3]) = 0;
    //bool isValidMove(int game[3][3]. int action);
    string getName() const;
    int getMaximumHP() const;
    int getCurrentHP() const;
    int getStrength() const;
    int getSpeed() const;
    int getMagic() const;
    virtual int getDamage() = 0;
    void takeDamage(int damage);
    virtual void reset() = 0;
    virtual void regenerate();
    virtual bool useAbility() = 0;
protected:
    string name;
    int speed;
    int hp;
    int maxHP;
    int strength;
    int magic;
    int damage2;
    int energy;
    int mana;
    int maxMana;
    int originalSpeed;
    int bonus_damage;
    int current_energy;
    int maximum_energy;
};