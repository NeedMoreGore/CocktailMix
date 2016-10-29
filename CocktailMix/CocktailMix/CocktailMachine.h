#pragma once

#include <string>
#include <vector>
#include "Cocktail.h"
#include "Dispenser.h"
#include <iostream>
#include "Ingredient.h"
#include <fstream>
#include <sstream>

using namespace std;

class CocktailMachine
{
public:
	CocktailMachine();
	~CocktailMachine();

	void makeCocktail(Cocktail*);
	void makeCocktail(int);
	vector<Cocktail*> getCocktails();
	vector<Ingredient*> getIngredients();

private:
	vector<Dispenser*> dispensers;
	vector<Cocktail*> cocktails;
	
	void exportCocktailSettings();
	void exportDispenserSettings();
	void importCocktailSettings();
	void importDispenserSettings();
};

