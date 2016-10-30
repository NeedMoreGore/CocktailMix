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
	system("cls"); //Clear console

	cout << "== CocktailMix | Mix it ==" << endl;
	cout << assembleSubmenu_make();
	cout << "0 - Exit" << endl;

	switch (getSelection())
	{
		case 0:
		{
			menu_main();
			return;
		}
		default:
		{
			submenu_make();
			break;
		}
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
		default:
		{
			submenu_configureDispenser();
			break;
		}

		//TODO: implement dynamic switch case
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

string Menue::assembleSubmenu_configureDispenser()
{
	string dispenserList = "";
	string ingredient;
	int pntrPos = 0;
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
