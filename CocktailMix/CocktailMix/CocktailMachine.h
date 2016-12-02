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
	vector<Cocktail*> getCocktails();
	vector<Ingredient*> getIngredients();
	vector<Dispenser*> getDispensers();

	//virtual methods
	virtual void makeCocktail(Cocktail*) = 0;
	virtual void makeCocktail(int) = 0;

protected:
	const string COCKTAIL_SETTINGS = "Cocktail.txt";
	const string DISPENSER_SETTINGS = "Dispenser.txt";
	static const int DISPENSER_SIZE = 6;

	vector<Dispenser*> dispensers;
	vector<Cocktail*> cocktails;

	void exportCocktailSettings();
	void exportDispenserSettings();
	void importCocktailSettings();
	void importDispenserSettings();

	static bool sortByNumber(Dispenser *lhs, Dispenser *rhs);
};
