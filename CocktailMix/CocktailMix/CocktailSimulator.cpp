#include "stdafx.h"
#include "CocktailSimulator.h"


CocktailSimulator::CocktailSimulator()
{
	//Load settings from txt files
	importCocktailSettings();
	importDispenserSettings();
}


CocktailSimulator::~CocktailSimulator()
{
	//export settings to txt files "CocktailSettings.txt" and "DispenserSettings.txt"
	exportCocktailSettings();
	exportDispenserSettings();

	for (Cocktail* cocktail : this->cocktails)
		delete cocktail;

	for (Dispenser* dispenser : this->dispensers)
		delete dispenser;
}


void CocktailSimulator::makeCocktail(Cocktail* cocktail)
{
	cocktail->print();
}

void CocktailSimulator::makeCocktail(int i)
{
	cocktails.at(i)->print();
}
