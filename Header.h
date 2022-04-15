#pragma once
class Character
{
public:
	void HungerLevel(int food);
	void ThirstLevel(int water);
	void WarmthLevel(int warmth);
	void EnergyLevel(int energy);
	void ConditionLevel(int points);
private:
	int hunger = 50, thirst = 50,
		warmth = 50, energy = 50, condition = 50;
};