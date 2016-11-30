#pragma once

#include "Cocktail.h"
#include "CocktailMachine.h"

//Implementation of CocktailMachine
class CocktailSimulator : public CocktailMachine
{
public:
	CocktailSimulator();
	~CocktailSimulator();

	void makeCocktail(Cocktail*);
	void makeCocktail(int);
private:
};

