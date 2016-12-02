#pragma once

#include "CocktailMachine.h"

class CocktailBot : public CocktailMachine
{
public:
	CocktailBot();
	~CocktailBot();

	void makeCocktail(Cocktail* cocktail);
	void makeCocktail(int i);
};

