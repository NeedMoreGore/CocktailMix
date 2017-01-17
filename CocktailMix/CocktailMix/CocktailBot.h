#pragma once

#include "CocktailMachine.h"
#include "DispenserApi.h"
#include <chrono>
#include <thread>
#include "Ingredient.h"

class CocktailBot : public CocktailMachine
{
public:
	CocktailBot();
	~CocktailBot();

	void makeCocktail(Cocktail* cocktail);
	void makeCocktail(int i);
};

