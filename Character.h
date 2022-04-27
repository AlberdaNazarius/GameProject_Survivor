#include <iostream>
class Character
{
public:
    static void ChangeHungerLevel(int food);
    static void ChangeThirstLevel(int water);
    static void ChangeWarmthLevel(int warmth);
    static void ChangeEnergyLevel(int energy);
    static void ChangeConditionLevel(int points);
    static int GetHungerLevel();
    static int GetThirstLevel();
    static int GetWarmthLevel();
    static int GetEnergyLevel();
    static int GetConditionLevel();
    static void Rest(int hours);
    static void DisplayCharacteristics();
private:
    int static hunger,
        thirst,
        warmth,
        energy,
        condition;
};



