#include "Character.h"
int Character::hunger = 100,
Character::thirst = 100,
Character::warmth = 100,
Character::energy = 100,
Character::condition = 100;
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
	if (energy > 0) Character::energy += energy * round((condition + warmth) / 200); // dependence between energy and warmth, condition
	if (energy < 0) Character::energy += energy * round(200 / (condition + warmth));  
	if (Character::energy > 100) Character::energy = 100;
}
void Character::ChangeConditionLevel(int points)
{
	if (points > 0) Character::condition += points * warmth / 100;
	if (points < 0) Character::condition += points * 100 / warmth;
	if (Character::condition > 100) Character::condition = 100;
}
void Character::Rest(int hours)
{
	Character::energy = hours * 13; // sleeping for 8 hours will fully restore energy
	if (Character::energy > 100) Character::energy = 100;
	Character::ChangeThirstLevel(hours * -2);
	Character::ChangeHungerLevel(hours * -2);
}
int Character::GetHungerLevel() { return hunger; }
int Character::GetThirstLevel() { return thirst; }
int Character::GetWarmthLevel() { return warmth; }
int Character::GetEnergyLevel() { return energy; }
int Character::GetConditionLevel() { return condition; }
