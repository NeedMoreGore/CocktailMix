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
	std::fill(dispenserFlow, dispenserFlow + DISPENSER_SIZE - 1, 0);
	bool running = true;
	controlDispenserFlow(cocktail, running);
}

void CocktailSimulator::makeCocktail(int i)
{
	cocktails.at(i)->print();
}

void CocktailSimulator::printDispenserStatus(int& second)
{
	string flowStatus = "  " + to_string(second) +  "\t - \t";

	for (int i = 0; i < DISPENSER_SIZE; i++)
	{
		if (dispenserFlow[i] != 0)
			flowStatus.append("ON  ");
		else
			flowStatus.append("OFF ");
		if (i < DISPENSER_SIZE - 1)
			flowStatus.append(" | ");
	}

	cout << flowStatus << endl;
}
void CocktailSimulator::loadDispenserFlow(Cocktail* cocktail)
{
	vector<Ingredient> ingredients = cocktail->getIngredients();

	for (int i = 0; i < DISPENSER_SIZE; i++)
	{
		for (Ingredient ingredient : ingredients)
		{
			if (dispensers[i]->getIngredient().getName() == ingredient.getName())
			{
				dispenserFlow[i] = stoi(cocktail->getQuantity(ingredient));
			}
		}
	}
}

void CocktailSimulator::controlDispenserFlow(Cocktail* cocktail, bool& running)
{
	int second = 0;

	loadDispenserFlow(cocktail);

	cout << "== CocktailMix | Making Cocktail: " + cocktail->getName() + " ==" << endl << endl;

	cout << " Time(s)  \t D1  |  D2  |  D3  |  D4  |  D5  |  D6  " << endl;
	do
	{
		running = false;

		printDispenserStatus(second);

		this_thread::sleep_for(std::chrono::milliseconds(1000));

		second++;

		for (int i = 0; i <= DISPENSER_SIZE; i++)
		{
			if (dispenserFlow[i] > 0)
			{
				dispenserFlow[i] --;
				running = true;
			}
		}

	} while (running == true);

	cout << endl << "Enjoy your cocktail!" << endl << endl;
}	
