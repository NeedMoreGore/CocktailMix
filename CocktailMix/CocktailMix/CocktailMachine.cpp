#include "stdafx.h"
#include "CocktailMachine.h"


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

void CocktailInterface::exportCocktailSettings()
{
	ofstream f;
	f.open(COCKTAIL_SETTINGS);

	for (Cocktail* cocktail : cocktails)
	{
		f << cocktail->getName() << ";"; //get cocktail name
		for (Ingredient ingredient : cocktail->getIngredients()) //get cocktail ingredients
		{
			f << ingredient.getName() << ";";
			f << cocktail->getQuantity(ingredient) << ";";
		}
		f << "\n"; //add new line
	}
	f.close();
}

void CocktailInterface::exportDispenserSettings()
{
	ofstream f;
	f.open(DISPENSER_SETTINGS);

	for (vector<Dispenser*>::iterator it = dispensers.begin(); it != dispensers.end(); ++it) //iterate through vector of dispensers
	{
		Ingredient ingredient = it[0]->getIngredient();
		f << it[0]->getNumber() << ";" << ingredient.getName() << ";" << '\n'; //write dispenser number and ingredient to file
	}
	f.close();
}


void CocktailInterface::importCocktailSettings()
{
	fstream f;
	stringstream is;
	string line;
	int i = 0; //keep track of iterations, first iteration of a line is the name of the cocktail followed by the ingredients

	f.open(COCKTAIL_SETTINGS, ios::in);

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
				//set ingredient name
				Ingredient ingredient;
				ingredient.setName(line);
				ingredients.push_back(ingredient);

				//set ingredient quantity
				getline(is, line, ';');
				cocktail->setQuantity(ingredient, line);
			}

		}

		cocktail->setName(name);
		cocktail->setIngredients(ingredients);
		this->cocktails.push_back(cocktail);
	}
}

// Sort container by number
bool CocktailInterface::sortByNumber(Dispenser *lhs, Dispenser *rhs) { int l = lhs->getNumber(); int r = rhs->getNumber(); return l < r; }

void CocktailInterface::importDispenserSettings()
{
	fstream f;
	stringstream is;
	string line;
	string temp[2]; //save dispenser values, [0]:dispenser number, [1]:ingredient name
	int i = 0;

	f.open(DISPENSER_SETTINGS, ios::in);

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

	sort(this->dispensers.begin(), this->dispensers.end(), sortByNumber); //sort by dispenser number

	f.close();
}

void CocktailSimulator::makeCocktail(Cocktail* cocktail)
{
	cocktail->print();
}

void CocktailSimulator::makeCocktail(int i)
{
	cocktails.at(i)->print();
}

vector<Cocktail*> CocktailInterface::getCocktails()
{
	return this->cocktails;
}

vector<Dispenser*> CocktailInterface::getDispensers()
{
	return this->dispensers;
}

vector<Ingredient*> CocktailInterface::getIngredients()
{
	vector<Ingredient*> ingredients;

	for (Cocktail* cocktail : this->cocktails) //iterate through all cocktails
	{
		for (Ingredient ingredient : cocktail->getIngredients()) //iterate through every ingredient of actual cocktail
		{
			Ingredient* newIngredient = new Ingredient(ingredient);

			if (ingredients.empty()) //if vector is empty
			{
				ingredients.push_back(newIngredient);
			}
			else //check if vector contains actual ingredient
			{
				for (vector<Ingredient*>::iterator it = ingredients.begin(); it != ingredients.end(); ++it)
				{
					if (it[0]->getName() == ingredient.getName()) //delete if vector contains ingredient
					{
						delete newIngredient;
						break;
					}
					else if(it == --ingredients.end()) //add if vector doesn't contain the ingredient
					{
						ingredients.push_back(newIngredient);
						break;
					}
				}
			}
		}
	}
	return ingredients;
}




