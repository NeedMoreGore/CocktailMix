#pragma once

#include "Cocktail.h"
#include "CocktailMachine.h"
#include <chrono>
#include <thread>

//Implementation of CocktailMachine
class CocktailSimulator : public CocktailMachine
{
public:
	CocktailSimulator();
	~CocktailSimulator();

	void makeCocktail(Cocktail*);
	void makeCocktail(int);
private:
	void printDispenserStatus(int& second);
	void loadDispenserFlow(Cocktail* cocktail);
	void controlDispenserFlow(Cocktail* cocktail, bool& running);

	int dispenserFlow[DISPENSER_SIZE] = { 0 };
};

