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
	//Verbindung herstellen und Api aktivieren
	int second = 0;
	bool running;
	vector<Dispenser*> dispensersList = getDispensers();
	vector<Ingredient> ingredientsList = cocktail->getIngredients();
	int quantityList[DISPENSER_SIZE] = { 0 };
	DispenserStatus status = DispenserStatus::Off;
	DispenserStatus statustest = DispenserStatus::Off;
	bool success;

	DispenserApi::Startup();

	DispenserApi::SetAllDispensers(DispenserStatus::Off);

	//set quantity
	for (Ingredient ingredient : ingredientsList)
	{
		for (Dispenser* dispenser : dispensersList)
		{
			if (dispenser->getIngredient().getName() == ingredient.getName())
			{
				quantityList[dispenser->getNumber() - 1] = stoi(cocktail->getQuantity(ingredient));
			}
		}
	}

	//make cocktail
	cout << "== CocktailMix | Making Cocktail: " + cocktail->getName() + " ==" << endl << endl;

	cout << " Time(s)  \t D1  |  D2  |  D3  |  D4  |  D5  |  D6  " << endl;

	do
	{
		string flowStatus = "  " + to_string(second) + "\t - \t";

		for (int i = 0; i < DISPENSER_SIZE; i++)
		{
			if (quantityList[i] > 0)
			{
				DispenserApi::SetDispenser(i + 1, DispenserStatus::On);
				//status = DispenserStatus::On;
			}
			else
			{
				DispenserApi::SetDispenser(i + 1, DispenserStatus::Off);
				//status = DispenserStatus::Off;
			}

			DispenserApi::GetDispenser(i + 1, statustest);

			if (status == DispenserStatus::On)
				flowStatus.append("ON  ");
			else
				flowStatus.append("OFF ");
			if (i < DISPENSER_SIZE - 1)
				flowStatus.append(" | ");
		}

		running = false;

		//printDispenserStatus(second)

		cout << flowStatus << endl;

		this_thread::sleep_for(std::chrono::milliseconds(1000));

		second++;

		for (int i = 0; i <= DISPENSER_SIZE; i++)
		{
			if (quantityList[i] > 0)
			{
				quantityList[i]--;
				running = true;
			}
		}



	} while (running == true);

	cout << endl << "Enjoy your cocktail!" << endl << endl;

	DispenserApi::SetAllDispensers(DispenserStatus::Off);

	//Verbindung abbauen und aufr�umen
	DispenserApi::Cleanup();
}

void CocktailBot::makeCocktail(int i)
{
	//ToDo: Implement
}
