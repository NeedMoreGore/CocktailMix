// CocktailMix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <list>
#include <limits>
#include <vector>
#include "Ingredient.h";
#include "Cocktail.h";
#include "Dispenser.h"
#include <fstream>

#include "CocktailMachine.h"

using namespace std;

const string VERSION = "0.1";
bool debugMode = true;

void showMainMenu()
{
	system("cls"); //Clear console

	cout << "== CocktailMix | V" << VERSION << " ==" << endl
		<< "1 - Make Cocktails" << endl
		<< "2 - Configure Cocktails" << endl
		<< "0 - Exit" << endl;
}

void showMakeCocktails()
{
	system("cls"); //Clear console

	cout << "== CocktailMix | Mix it ==" << endl
		<< "0 - Exit" << endl;
}

void showConfigureCocktailMix()
{
	system("cls"); //Clear console

	cout << "== CocktailMix | Configure ==" << endl
		<< "1 - List Dispenser-Slot" << endl
		<< "2 - Edit Dispenser-Slot" << endl
		<< "3 - List Ingredients" << endl
		<< "4 - Add Ingredient" << endl
		<< "5 - Edit / Delete Ingredient" << endl
		<< "6 - List Cocktail" << endl
		<< "7 - Add Cocktail" << endl
		<< "8 - Edit Cocktail" << endl
		<< "0 - Exit" << endl;
}

void getSelection(int &selection)
{
	cout << "\nSelection: ";

	cin >> selection;

	while (cin.fail()) //catch input errors
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Enter a NUMBER: ";
		cin >> selection;
	}
}

void createSettingsFile() //debug method
{
	fstream f;

	f.open("CocktailSettings.txt", ios::out);
	f << "Tequila Sunrise;Tequila;Orangensaft;Grenadine;\nScrewdriver;Vodka;Orangensaft;";
	f.close();

	f.open("DispenserSettings.txt", ios::out);
	f << "1;Vodka;\n2;Tequila;\n3;Orangensaft;\n4;Grenadine;";
	f.close();

}

/*
MAIN
*/
int main()
{

	CocktailMachine* bla = new CocktailMachine();

	createSettingsFile();

	int selection = -1;

	while (true)
	{
		switch (selection)
		{
			case 1: // Make CocktailMix
			{
				while (true)
				{
					showMakeCocktails(); //show Menu
					getSelection(selection); //get user menu selection

					switch (selection) //Submenu
					{
						case 0: //Exit submenu
							break;

						default:
							continue;
					}
					break;
				}
				selection = -1; //reset selection
				break;
			}
			case 2: // Configure CocktailMix
			{
				while(true)
				{
					showConfigureCocktailMix(); //show menu
					getSelection(selection); //get user menu selection

					switch (selection) //submenu
					{
						case 0: //Exit submenu
							break;

						default: 
							continue;
					}
					break;
				}
				selection = -1; //reset selection
				break;
			}
			case 0: //Exit program
			{
				delete bla;
				return 0;
			}
			default: //show main menu
			{
				showMainMenu(); //show menu
				getSelection(selection); //get user menu selection
				break;
			}
		}
	}
}



