#include "stdafx.h"
#include "CocktailMachine.h"


CocktailMachine::CocktailMachine()
{
	//Load settings from txt files
	importCocktailSettings();
	importDispenserSettings();
}


CocktailMachine::~CocktailMachine()
{
	//export settings to txt files "CocktailSettings.txt" and "DispenserSettings.txt"
	exportCocktailSettings();
	exportDispenserSettings();
}

void CocktailMachine::exportCocktailSettings()
{
	ofstream f;
	f.open("CocktailSettings.txt");

	for (Cocktail* cocktail : cocktails)
	{
		f << cocktail->getName() << ";"; //get cocktail name
		for (Ingredient ingredient : cocktail->getIngredients()) //get cocktail ingredients
			f << ingredient.getName() << ";";
		f << "\n"; //add new line
	}
	f.close();
}

void CocktailMachine::exportDispenserSettings()
{
	ofstream f;
	f.open("DispenserSettings.txt");

	for (vector<Dispenser*>::iterator it = dispensers.begin(); it != dispensers.end(); ++it) //iterate through vector of dispensers
	{
		Ingredient ingredient = it[0]->getIngredient();
		f << it[0]->getNumber() << ";" << ingredient.getName() << ";" << '\n'; //write dispenser number and ingredient to file
	}
	f.close();
}


void CocktailMachine::importCocktailSettings()
{
	fstream f;
	stringstream is;
	string line;
	int i = 0; //keep track of iterations, first iteration of a line is the name of the cocktail followed by the ingredients

	f.open("CocktailSettings.txt", ios::in);

	while (getline(f, line))
	{
		i = 0;

		is.clear();
		is.str(line);

		Cocktail* cocktail = new Cocktail();

		string name;
		vector<Ingredient> ingredients;
		
		while (getline(is, line, ';'))
		{
			i++;

			if (i == 1) //get name, first item in a line
				name = line;
			else //get ingredients
			{
				Ingredient ingredient;
				ingredient.setName(line);
				ingredients.push_back(ingredient);
			}
		}

		cocktail->setName(name);
		cocktail->setIngredients(ingredients);
		this->cocktails.push_back(cocktail);
	}
}

void CocktailMachine::importDispenserSettings()
{
	fstream f;
	stringstream is;
	string line;
	string temp[2]; //save dispenser values, [0]:dispenser number, [1]:ingredient name
	int i = 0;

	f.open("DispenserSettings.txt", ios::in);

	while (getline(f, line))
	{
		i = 0;

		is.clear();
		is.str(line);

		Dispenser* dispenser = new Dispenser();
		Ingredient* ingredient = new Ingredient();

		while (getline(is, line, ';'))
		{
			temp[i] = line;
			i++;
		}

		ingredient->setName(temp[1]); //set name of ingredient

		dispenser->setNumber(stoi(temp[0])); //cast dispenser number to int
		dispenser->setIngredient(*ingredient);
		this->dispensers.push_back(dispenser);
	}
	f.close();
}





