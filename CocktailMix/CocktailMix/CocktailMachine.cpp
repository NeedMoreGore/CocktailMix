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
				cout << "Pushed to Cocktail: " << ingredient.getName();
			}
		}

		cocktail->setName(name);
		cocktail->setIngredients(ingredients);
		this->cocktails.push_back(cocktail);
		system("pause");
	}
}

// Sort container by number
bool CocktailMachine::sortByNumber(Dispenser *lhs, Dispenser *rhs) { int l = lhs->getNumber(); int r = rhs->getNumber(); return l < r; }

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

	sort(this->dispensers.begin(), this->dispensers.end(), sortByNumber); //sort by dispenser number

	f.close();
}

void CocktailMachine::makeCocktail(Cocktail* cocktail)
{
	cocktail->print();
}

vector<Cocktail*> CocktailMachine::getCocktails()
{
	return this->cocktails;
}

vector<Dispenser*> CocktailMachine::getDispensers()
{
	return this->dispensers;
}

vector<Ingredient*> CocktailMachine::getIngredients()
{
	vector<Ingredient*> ingredients;

	cout << "Cocktails-Vector-Size: " << this->cocktails.size();

	for (Cocktail* cocktail : this->cocktails)
	{
		for (Ingredient ingredient : cocktail->getIngredients())
		{
			Ingredient* newIngredient = new Ingredient(ingredient);

			cout << "New-Ingredient: " << ingredient.getName();
			
			if (ingredients.empty())
			{
				ingredients.push_back(newIngredient);
			}
			else
			{
				for (vector<Ingredient*>::iterator it = ingredients.begin(); it != ingredients.end(); ++it)
				{
					if (it[0]->getName() == ingredient.getName())
					{
						cout << "Deleted: " << ingredient.getName();
						delete newIngredient;
						break;
					}
					else if(it == --ingredients.end())
					{
						cout << "Pushed: " << ingredient.getName();
						ingredients.push_back(newIngredient);
						break;
					}
				}
			}
		}
	}

	system("pause");
	return ingredients;
}




