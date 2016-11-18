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

class CocktailInterface
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

	vector<Dispenser*> dispensers;
	vector<Cocktail*> cocktails;

	void exportCocktailSettings();
	void exportDispenserSettings();
	void importCocktailSettings();
	void importDispenserSettings();

	static bool sortByNumber(Dispenser *lhs, Dispenser *rhs);
};

//Implementation of CocktailInterface
class CocktailSimulator : public CocktailInterface
{
public:	
	CocktailSimulator();
	~CocktailSimulator();

	void makeCocktail(Cocktail*);
	void makeCocktail(int);
private:
};

