#ifndef FIGHTERINTERFACE_HPP_
#define FIGHTERINTERFACE_HPP_

#include <iostream>
#include <string>
#include <vector>

/*
*	WARNING: It is expressly forbidden to modify any part of this document, including its name
*/

/*
*	This class specifies the methods for a fighter.
*
*	All fighters have the following attributes:
*		Name - The fighter's name
*		Hit Points - The amount of health the fighter has, with a specified maximum; reaching 0 is equivalent to losing. A Fighter's
*			starting Hit Points (which is a Fighter's maximum Hit Points) must be greater than 0. There is no upper bound to what
*			a Fighter's starting/maximum Hit Points could be.
*		Strength - Physical power, used to determine hit point regeneration. Must be greater than 0. No maximum value.
*		Speed - Dexterity and physical movement, used to reduce damage when being attacked. Must be greater than 0. No maximum value.
*		Magic - Magical prowess, used for some special abilities. Must be greater than 0. No maximum value.
*
*	The three fighter types have unique abilities:
*		Robot - Relies on strength to deal damage.  Also can use stored energy to temporarily increase damage (max/starting energy equal to 2*magic).
*			Only Robots have energy.
*		Archer - Relies on speed to deal damage.  Also can increase its speed for the remainder of the battle (no max bonus speed).
*		Cleric - Relies on magic to deal damage.  Also can heal itself using mana, restoring hit points (max/starting mana equal to 5*magic).
*			Only Clerics have mana.
*
*	More details about how stats are used and how abilities work can be found in the comments below.
*/

/*
*	ROBOT_ABILITY_COST
*	The amount of energy a Robot needs to perform its special ability.
*/
const int ROBOT_ABILITY_COST = 5;

/*
*	CLERIC_ABILITY_COST
*	The amount of mana a Cleric needs to perform its special ability.
*/
const int CLERIC_ABILITY_COST = 25;

class FighterInterface
{
public:
	FighterInterface() {}
	virtual ~FighterInterface() {}

	/*
	*	getName()
	*
	*	Returns the name of this fighter.
	*/
	virtual std::string getName() const = 0;

	/*
	*	getMaximumHP()
	*
	*	Returns the maximum hit points of this fighter.
	*/
	virtual int getMaximumHP() const = 0;

	/*
	*	getCurrentHP()
	*
	*	Returns the current hit points of this fighter.
	*/
	virtual int getCurrentHP() const = 0;

	/*
	*	getStrength()
	*
	*	Returns the strength stat of this fighter.
	*/
	virtual int getStrength() const = 0;

	/*
	*	getSpeed()
	*
	*	Returns the speed stat of this fighter.
	*/
	virtual int getSpeed() const = 0;

	/*
	*	getMagic()
	*
	*	Returns the magic stat of this fighter.
	*/
	virtual int getMagic() const = 0;

	/*
	*	getDamage()
	*
	*	Returns the amount of damage a fighter will deal.
	*
	*	Robot:
	*	This value is equal to the Robot's strength plus any additional damage added for having just used its special ability.
	*
	*	Archer:
	*	This value is equal to the Archer's speed.
	*
	*	Cleric:
	*	This value is equal to the Cleric's magic.
	*/
	virtual int getDamage() = 0;

	/*
	*	takeDamage(int)
	*
	*	Reduces the fighter's current hit points by an amount equal to the given
	*	damage minus one fourth of the fighter's speed.  This method must reduce
	*	the fighter's current hit points by at least one.  It is acceptable for
	*	this method to give the fighter negative current hit points.
	*
	*	Examples:
	*		damage=10, speed=7		=> damage_taken=9
	*		damage=10, speed=9		=> damage_taken=8
	*		damage=10, speed=50		=> damage_taken=1
	*/
	virtual void takeDamage(int damage) = 0;

	/*
	*	reset()
	*
	*	Restores a fighter's current hit points to its maximum hit points.
	*
	*	Robot:
	*	Also restores a Robot's current energy to its maximum value (which is 2 times its magic).
	*	Also resets a Robot's bonus damage (calculated when a Robot uses its ability) to 0.
	*
	*	Archer:
	*	Also resets an Archer's current speed to its original value.
	*
	*	Cleric:
	*	Also restores a Cleric's current mana to its maximum value (which is 5 times its magic).
	*/
	virtual void reset() = 0;

	/*
	*	regenerate()
	*
	*	Increases the fighter's current hit points by an amount equal to one sixth of
	*	the fighter's strength.  This method must increase the fighter's current hit
	*	points by at least one.  Do not allow the current hit points to exceed the
	*	maximum hit points.
	*
	*	Cleric:
	*	Also increases a Cleric's current mana by an amount equal to one fifth of the
	*	Cleric's magic.  This method must increase the Cleric's current mana by at
	*	least one.  Do not allow the current mana to exceed the maximum mana (again, 5 times its magic).
	*/
	virtual void regenerate() = 0;

	/*
	*	useAbility()
	*
	*	Attempts to perform a special ability based on the type of fighter.  The
	*	fighter will attempt to use this special ability just prior to attacking
	*	every turn.

	*	
	*
	*	Return true if the ability was used; false otherwise.
	*/
	virtual bool useAbility() = 0;
};

#endif /* FIGHTERINTERFACE_HPP_ */
