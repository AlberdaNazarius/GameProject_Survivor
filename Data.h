#pragma once
#include <iostream>
#include <list>

class Data
{
public:
	static int GetEnvironment(int index);
protected:
	static std::list<int> EnvironmentsSequence;
};
