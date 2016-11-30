#include "stdafx.h"
#include "Menue.h"

Menue* Menue::menue;

Menue::Menue(string version, CocktailMachine* machine)
{
	this->machine = machine;
	this->version = version;
	menu_main();
}

Menue::~Menue()
{
}

void Menue::createMenue(string version, CocktailMachine * machine)
{
	if (menue == nullptr)
		menue = new Menue(version,machine);
}

void Menue::releaseMenue()
{
	if (menue != nullptr)
		delete menue;
}

void Menue::menu_main() //print main menu to console and get user selection
{
	system("cls"); //Clear console

	cout << "== CocktailMix | V" << version << " ==" << endl << endl
		<< "[1] - Make Cocktails" << endl
		<< "[2] - Configure Cocktails" << endl << endl
		<< "[0] - Exit" << endl;

	switch (getSelection())
	{
		case 1:  //print submenu make cocktails
		{
			submenu_make();
			break;
		}
		case 2:  //print submenu configure cocktails
		{
			submenu_configure();
			break;
		}
		case 0: //exit program
		{
			return;
		}
		default: //wrong selection
		{
			menu_main();
			break;
		}
	}

}

void Menue::submenu_make()
{
	int unsigned selection = 0;
	system("cls"); //Clear console

	cout << "== CocktailMix | Mix it ==" << endl << endl;
	cout << assembleSubmenu_make() << endl; //dynamically assemble menu navigation string with available cocktails
	cout << "[0] - Return" << endl;

	selection = getSelection();

	if (selection == 0) //leave submenu
	{
		menu_main();
		return;
	}
	else if (selection <= selectionSubmenu_make().size()) //compare if input is in available selection range (= number of cocktails provided in settings)
	{
		system("cls");
		selectionSubmenu_make()[selection]->print(); //print selected cocktail
		system("pause");
		submenu_make(); //show submenu again
		return;
	}
	else //do nothing
	{
		submenu_make();
		return;
	}
}

void Menue::submenu_configure()
{
	system("cls"); //Clear console

	cout << "== CocktailMix | Configure ==" << endl << endl
		<< "[1] - Configure Dispensers" << endl
		<< "[2] - List Cocktail" << endl
		<< "[3] - Add Cocktail" << endl
		<< "[4] - Edit Cocktail" << endl
		<< "[5] - Delete Cocktail" << endl << endl
		<< "[0] - Return" << endl;

	switch (getSelection())
	{
		case 0: //leave submenu
		{
			menu_main();
			return;
		}
		case 1: //enter submenu configure dispenser
		{
			submenu_configureDispenser();
			break;
		}
		default: //do nothing
		{
			submenu_configure();
			break;
		}
	}
}

void Menue::submenu_configureDispenser()
{
	system("cls"); //Clear console

	cout << "== CocktailMix | Configure Dispenser ==" << endl << endl;
	cout << assembleSubmenu_configureDispenser() << endl; //assemble menu navigation string for available dispensers (provided by dispenser settings)
	cout << "[0] - Return" << endl;

	switch (getSelection())
	{
		case 0: //leave submenu
		{
			submenu_configure();
			return;
		}
		case 1: //select dispenser(dispenserNumber) and open new submenu -> select ingredient for dispenser
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
		default: //do nothing
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

	cout << "== CocktailMix | Select Ingredient ==" << endl << endl;
	cout << assembleSubmenu_selectIngredient() << endl; //assemble navigation string for ingredients (provided by cocktails in cocktail settings)
	cout << "[0] - Return" << endl;
	try
	{
		switch (getSelection())
		{
		case 0: //leave submenu
		{
			submenu_configureDispenser();
			return;
		}
		case 1: //assign new ingredient to dispenser and exit submenu
		{
			tempDispenser = machine->getDispensers().at(dispenserNumber - 1); //get pntr to dispenser
			tempDispenser->setIngredient(*machine->getIngredients().at(0)); //set new ingredient
			submenu_configureDispenser(); //exit submenu
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
		case 7:
		{
			tempDispenser = machine->getDispensers().at(dispenserNumber - 1);
			tempDispenser->removeIngredient();
			submenu_configureDispenser();
			break;
		}
		default: //do nothing
		{
			submenu_selectIngredient(dispenserNumber);
			break;
		}
		}
	}
	catch (exception e)
	{
		submenu_selectIngredient(dispenserNumber);
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
		cocktailList.append("[" + to_string(i) + "]" + " - " + it[0]->getName() + "\n"); //append cocktails to string
	}
	return cocktailList;
}
/*
Map every available cocktail to a different int value and return the map.
Needed for cocktail selection by user input

@return: map<int, Cocktail*>
*/

map<int, Cocktail*> Menue::selectionSubmenu_make()
{
	map<int, Cocktail*> cocktailMap;

	int i = 0;
	vector<Cocktail*> cocktails = this->machine->getCocktails();

	for (vector<Cocktail*>::iterator it = cocktails.begin(); it != cocktails.end(); ++it) //iterate through vector of cocktails
	{
		i++;
		cocktailMap[i] = it[0]; //save pointer to cocktail in map, need for dynamic selection (=> cocktailMap[selection] = pntr to selected cocktail)
	}
	return cocktailMap;
}

/*
Dynamically create menu string with dispenser configurations

@return: string
*/
string Menue::assembleSubmenu_configureDispenser()
{
	string dispenserList = "";										//menue string (return value) 
	string ingredient;												//ingredient name
	unsigned int pntrPos = 0;										//vector position
	int dispenserSize = 6;											//max. dispenser size
	vector<Dispenser*> dispensers = this->machine->getDispensers(); //vector with all dispensers
	Dispenser* pntr = dispensers[pntrPos];							//pointer to first dispenser

	for (int i = 1; i <= dispenserSize; i++) //note: only works if vector<Dispenser*> is sorted
	{
		if (pntr->getNumber() == i && pntr != nullptr) //check if dispenser is configured
		{
			ingredient = pntr->getIngredient().getName();
			if (dispensers.size() > pntrPos + 1)
				pntrPos++;
			pntr = dispensers[pntrPos];
		}
		else //set to "free" if dispenser holds no ingredient
			ingredient = "free";

		dispenserList.append("[" + to_string(i) + "]" + " - " + ingredient + "\n");
	}

	return dispenserList;
}

/*
Dynamically create menu string, a selection menu with all ingredients, to configure the selected dispenser

@return: string
*/
string Menue::assembleSubmenu_selectIngredient()
{
	string ingredientsList = "";

	for (unsigned int i = 0; i < machine->getIngredients().size(); i++) //get all available ingredients and append to string
	{
		ingredientsList.append("[" + to_string(i + 1) + "]" + " - " + machine->getIngredients().at(i)->getName() + "\n");
	}

	ingredientsList.append("\n[7] - Remove ingredient from dispenser \n");

	return ingredientsList;
}
