#pragma once

#include <iostream>
#include <string>
#include "CocktailMachine.h"
#include "Cocktail.h"
#include "Dispenser.h"
#include <map>

using namespace std;

class Menue
{
public:
	Menue(string version, CocktailMachine* machine);
	~Menue();

private:
	void menu_main();
	void submenu_make();
	void submenu_configure();
	void submenu_configureDispenser();
	void submenu_selectIngredient(int dispenserNumber);
	int getSelection();
	map<int, Cocktail*> selectionSubmenu_make();
	string assembleSubmenu_make();
	string assembleSubmenu_configureDispenser();
	string assembleSubmenu_selectIngredient();
	string version;
	CocktailMachine* machine;
};

