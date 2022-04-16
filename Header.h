#pragma once
class Character
{
public:
	void ChangeHungerLevel(int food);
	void ChangeThirstLevel(int water);
	void ChangeWarmthLevel(int warmth);
	void ChangeEnergyLevel(int energy);
	void ChangeConditionLevel(int points);
private:
	int hunger = 50,
		hirst = 50,
		warmth = 50, 
		energy = 50, 
		condition = 50;
};