#pragma once
#include <map>

class IData
{
public:
	virtual void DisplayStats() = 0;
	virtual std::map<std::string, int> WhatToSave() = 0;
	virtual void ReloadData(std::map<std::string, int> data) = 0;
	virtual void SetDeffaultCharacteristics() = 0;
};