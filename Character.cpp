#include "Character.h"
int Character::hunger = 50,
Character::thirst = 50,
Character::warmth = 50,
Character::energy = 50,
Character::condition = 50;
#include <math.h>
#include <iostream>
void Character::ChangeHungerLevel(int food)
{
	Character::hunger += food;
	if (Character::hunger > 100) Character::hunger = 100;
}
void Character::ChangeThirstLevel(int water)
{
	Character::thirst += water;
	if (Character::thirst > 100) Character::thirst = 100;
}
void Character::ChangeWarmthLevel(int warmth)
{
    Character::warmth += warmth;
	if (Character::warmth > 100) Character::warmth = 100;
    // std::cout << Character::warmth; // test
}
void Character::ChangeEnergyLevel(int energy)
{
	Character::energy += energy * round(200 / (condition + warmth)); // dependence between energy and warmth, condition
	if (Character::energy > 100) Character::energy = 100;
}
void Character::ChangeConditionLevel(int points)
{
	Character::condition += points;
	if (Character::condition > 100) Character::condition = 100;
}
