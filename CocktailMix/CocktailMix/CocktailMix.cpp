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


void createSettingsFile() //create test data
{
	fstream f;

	f.open("Cocktail.txt", ios::out);
	f << "Tequila Sunrise;Tequila;40;Orangensaft;150;Grenadine;10;\nScrewdriver;Vodka;40;Orangensaft;80;";
	f.close();

	f.open("Dispenser.txt", ios::out);
	f << "1;Vodka;\n2;Tequila;\n3;Orangensaft;\n4;Grenadine;\n5;free;\n6;free;";
	f.close();
}

/*
MAIN
*/
int main()
{
	//createSettingsFile();
	CocktailInterface* machine = new CocktailSimulator();
	Menue* menue = new Menue(VERSION, machine); //constructor call starts menu 
	delete menue;
	delete (CocktailSimulator*)machine; //Cast to CocktailSimulator, otherwise destructor cannot be called
	return 0;
}



