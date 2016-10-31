#pragma once

#include <string>
#include <vector>
#include "Cocktail.h"
#include "Dispenser.h"
#include <iostream>
#include "Ingredient.h"
#include <fstream>
#include <sstream>
#include <algorithm>

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
	vector<Dispenser*> getDispensers();

private:
	vector<Dispenser*> dispensers;
	vector<Cocktail*> cocktails;
	
	static bool CocktailMachine::sortByNumber(Dispenser *lhs, Dispenser *rhs);
	void exportCocktailSettings();
	void exportDispenserSettings();
	void importCocktailSettings();
	void importDispenserSettings();
};

