// CocktailMix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Ingredient.h"
#include "Cocktail.h"
#include "Dispenser.h"
#include "Menue.h"
#include "CocktailMachine.h"

#include <iostream>
#include <string>
#include <list>
#include <limits>
#include <vector>
#include <fstream>

using namespace std;

const string VERSION = "0.2";


void createSettingsFile() //debug method
{
	fstream f;

	f.open("CocktailSettings.txt", ios::out);
	f << "Tequila Sunrise;Tequila;Orangensaft;Grenadine;\nScrewdriver;Vodka;Orangensaft;";
	f.close();

	f.open("DispenserSettings.txt", ios::out);
	f << "1;Vodka;\n2;Tequila;\n3;Orangensaft;\n4;Grenadine;\n5;free;\n6;free";
	f.close();
}

/*
MAIN
*/
int main()
{
	//createSettingsFile();
	CocktailMachine* machine = new CocktailMachine(); 
	Menue* menue = new Menue(VERSION, machine); //constructor calls main menu 
	delete menue;
	delete machine;
	return 0;
}



