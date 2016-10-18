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
	#include "Dispenser.h";

	using namespace std;

	const string VERSION = "0.1";
	bool debugMode = false;

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

		while (std::cin.fail()) //catch input errors
		{
			std::cin.clear();
			std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
			std::cout << "Bad entry. Enter a NUMBER: ";
			cin >> selection;
		}
	}

	void test()
	{
		Ingredient *orangeJuice = new Ingredient();
		Ingredient *tequila = new Ingredient();
		Ingredient *grenadine = new Ingredient();

		orangeJuice->setName("Orange Juice");
		tequila->setName("Tequila");
		grenadine->setName("Grenadine");

		vector<Ingredient> ingredients;

		
		ingredients.push_back(*orangeJuice);
		ingredients.push_back(*tequila);
		ingredients.push_back(*grenadine);

		Cocktail *dummyCocktail = new Cocktail();
		dummyCocktail->setName("Tequila Sunrise");
		dummyCocktail->setIngredients(ingredients);

		dummyCocktail->print();
	}

	void debugFunction(bool debugMode)
	{
		if (debugMode)
		{
			test();

			system("pause");
		}
	}

	/*
	MAIN
	*/
	int main()
	{
		int selection = -1;

		debugFunction(debugMode);

		while (true)
		{
			switch (selection)
			{
//Req 02
				case 1: // Make CocktailMix
				{
					while (true)
					{
						showMakeCocktails(); //show Menu
						getSelection(selection); //get user menu selection

						switch (selection)
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
//Req03
				case 2: // Configure CocktailMix
				{
					while(true)
					{
						showConfigureCocktailMix(); //show menu
						getSelection(selection); //get user menu selection

						switch (selection)
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
//Req03
				case 0: //Exit program
					return 0;
//Req01
				default: //show main menu
				{
					showMainMenu(); //show menu
					getSelection(selection); //get user menu selection
					break;
				}
			}
		}
	}



