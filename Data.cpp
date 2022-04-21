#include "Data.h"
#include <iostream>
#include <list>

int Data::GetEnvironment(int index)
{
	if (Data::EnvironmentsSequence.size() > index)
		return *next(Data::EnvironmentsSequence.begin(), index);
	else
		throw("There is no such index!");
}