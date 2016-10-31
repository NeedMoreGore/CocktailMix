#include "stdafx.h"
#include "Menue.h"


Menue::Menue(string version, CocktailMachine* machine)
{
	this->machine = machine;
	this->version = version;
	menu_main();
}


Menue::~Menue()
{
}

void Menue::menu_main()
{
	system("cls"); //Clear console

	cout << "== CocktailMix | V" << version << " ==" << endl
		<< "1 - Make Cocktails" << endl
		<< "2 - Configure Cocktails" << endl
		<< "0 - Exit" << endl;

	switch (getSelection())
	{
		case 1:
		{
			submenu_make(); //show submenu make cocktails
			break;
		}
		case 2:
		{
			submenu_configure();
			break;
		}
		case 0:
		{
			return;
		}
		default:
		{
			menu_main();
			break;
		}
	}

}

void Menue::submenu_make()
{
	int selection = 0;
	system("cls"); //Clear console

	cout << "== CocktailMix | Mix it ==" << endl;
	cout << assembleSubmenu_make();
	cout << "0 - Exit" << endl;

	selection = getSelection();

	if (selection == 0)
	{
		menu_main();
		return;
	}
	else if (selection <= selectionSubmenu_make().size())
	{
		system("cls");
		selectionSubmenu_make()[selection]->print();
		system("pause");
		submenu_make();
		return;
	}
	else
	{
		submenu_make();
		return;
	}
}

void Menue::submenu_configure()
{
	system("cls"); //Clear console

	cout << "== CocktailMix | Configure ==" << endl
		<< "1 - Configure Dispensers" << endl
		<< "2 - List Cocktail" << endl
		<< "3 - Add Cocktail" << endl
		<< "4 - Edit Cocktail" << endl
		<< "5 - Delete Cocktail" << endl
		<< "0 - Exit" << endl;

	switch (getSelection())
	{
		case 0:
		{
			menu_main();
			return;
		}
		case 1:
		{
			submenu_configureDispenser();
			break;
		}
		default:
		{
			submenu_configure();
			break;
		}
	}
}

void Menue::submenu_configureDispenser()
{
	system("cls"); //Clear console

	cout << "== CocktailMix | Configure Dispenser ==" << endl;
	cout << assembleSubmenu_configureDispenser();
	cout << "0 - Exit";

	switch (getSelection())
	{
		case 0:
		{
			submenu_configure();
			return;
		}
		case 1:
		{
			submenu_selectIngredient(1);
			break;
		}
		case 2:
		{
			submenu_selectIngredient(2);
			break;
		}
		case 3:
		{
			submenu_selectIngredient(3);
			break;
		}
		case 4:
		{
			submenu_selectIngredient(4);
			break;
		}
		case 5:
		{
			submenu_selectIngredient(5);
			break;
		}
		case 6:
		{
			submenu_selectIngredient(6);
			break;
		}
		default:
		{
			submenu_configureDispenser();
			break;
		}
	}
}

int Menue::getSelection()
{
	int selection = -1;

	cout << "\nSelection: ";

	cin >> selection;

	while (cin.fail()) //catch input errors
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Enter a NUMBER: ";
		cin >> selection;
	}

	return selection;
}

void Menue::submenu_selectIngredient(int dispenserNumber)
{
	Dispenser* tempDispenser;

	system("cls"); //Clear console

	cout << "== CocktailMix | Select Ingredient ==" << endl;
	cout << assembleSubmenu_selectIngredient();
	cout << "0 - Exit";

	switch (getSelection())
	{
		case 0:
		{
			submenu_configure();
			return;
		}
		case 1:
		{
			tempDispenser = machine->getDispensers().at(dispenserNumber - 1);
			tempDispenser->setIngredient(*machine->getIngredients().at(0));
			submenu_configureDispenser();
			break;
		}
		case 2:
		{
			tempDispenser = machine->getDispensers().at(dispenserNumber - 1);
			tempDispenser->setIngredient(*machine->getIngredients().at(1));
			submenu_configureDispenser();
			break;
		}
		case 3:
		{
			tempDispenser = machine->getDispensers().at(dispenserNumber - 1);
			tempDispenser->setIngredient(*machine->getIngredients().at(2));
			submenu_configureDispenser();
			break;
		}
		case 4:
		{
			tempDispenser = machine->getDispensers().at(dispenserNumber - 1);
			tempDispenser->setIngredient(*machine->getIngredients().at(3));
			submenu_configureDispenser();
			break;
		}
		case 5:
		{
			tempDispenser = machine->getDispensers().at(dispenserNumber - 1);
			tempDispenser->setIngredient(*machine->getIngredients().at(4));
			submenu_configureDispenser();
			break;
		}
		case 6:
		{
			tempDispenser = machine->getDispensers().at(dispenserNumber - 1);
			tempDispenser->setIngredient(*machine->getIngredients().at(5));
			submenu_configureDispenser();
			break;
		}
		default:
		{
			submenu_selectIngredient(dispenserNumber);
			break;
		}
	}
}

string Menue::assembleSubmenu_make()
{
	string cocktailList = "";
	int i = 0;
	vector<Cocktail*> cocktails = this->machine->getCocktails();

	for (vector<Cocktail*>::iterator it = cocktails.begin(); it != cocktails.end(); ++it) //iterate through vector of cocktails
	{
		i++;
		cocktailList.append(to_string(i) + " - " + it[0]->getName() + "\n");
	}
	return cocktailList;
}

map<int, Cocktail*> Menue::selectionSubmenu_make()
{
	map<int, Cocktail*> cocktailMap;

	int i = 0;
	vector<Cocktail*> cocktails = this->machine->getCocktails();

	for (vector<Cocktail*>::iterator it = cocktails.begin(); it != cocktails.end(); ++it) //iterate through vector of cocktails
	{
		i++;
		cocktailMap[i] = it[0];
	}
	return cocktailMap;
}
string Menue::assembleSubmenu_configureDispenser()
{
	string dispenserList = "";
	string ingredient;
	unsigned int pntrPos = 0;
	int i = 6; //dispenserSize
	vector<Dispenser*> dispensers = this->machine->getDispensers();
	Dispenser* pntr = dispensers[pntrPos];

	for (int i = 1; i <= 6; i++)
	{
		if (pntr->getNumber() == i && pntr != NULL)
		{
			ingredient = pntr->getIngredient().getName();
			if (dispensers.size() > pntrPos + 1)
				pntrPos++;
			pntr = dispensers[pntrPos];
		}
		else
			ingredient = "free";

		dispenserList.append(to_string(i) + " - " + ingredient + "\n");
	}
	return dispenserList;

	//TODO: redo behaviour
}

string Menue::assembleSubmenu_selectIngredient()
{
	string ingredientsList = "";

	cout << "Size: " << machine->getIngredients().size();

	for (unsigned int i = 0; i < machine->getIngredients().size(); i++)
	{
		cout << "Name " << machine->getIngredients().at(i)->getName() << endl;
		ingredientsList.append(to_string(i + 1) + " - " + machine->getIngredients().at(i)->getName() + "\n");
	}

	return ingredientsList;
}
