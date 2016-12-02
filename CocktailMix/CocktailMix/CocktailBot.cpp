#include "stdafx.h"

#include "CocktailBot.h"


CocktailBot::CocktailBot()
{
	//Load settings from txt files
	importCocktailSettings();
	importDispenserSettings();
}


CocktailBot::~CocktailBot()
{
	//export settings to txt files "CocktailSettings.txt" and "DispenserSettings.txt"
	exportCocktailSettings();
	exportDispenserSettings();

	for (Cocktail* cocktail : this->cocktails)
	delete cocktail;

	for (Dispenser* dispenser : this->dispensers)
	delete dispenser;
}

void CocktailBot::makeCocktail(Cocktail* cocktail)
{
	//ToDo: Implement
}

void CocktailBot::makeCocktail(int i)
{
	//ToDo: Implement
}
