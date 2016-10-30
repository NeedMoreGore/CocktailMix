#pragma once

#include <iostream>
#include <string>
#include "CocktailMachine.h"
#include "Cocktail.h"

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
	int getSelection();
	string assembleSubmenu_make();
	string Menue::assembleSubmenu_configureDispenser();
	string version;
	CocktailMachine* machine;
};

