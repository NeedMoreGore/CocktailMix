#include "stdafx.h"
#include "Cocktail.h"
#include <iostream>


Cocktail::Cocktail()
{
	this->name = "";
}

Cocktail::~Cocktail()
{
}

void Cocktail::setName(string name)
{
	this->name = name;
}

string Cocktail::getName()
{
	return this->name;
}

void Cocktail::setIngredients(vector<Ingredient> ingredients)
{
	this->ingredients = ingredients;
}

vector<Ingredient> Cocktail::getIngredients()
{
	return this->ingredients;
}

void Cocktail::print() //print cocktail name + ingredients
{
	cout << "== Cocktail | Ingredients ==" << endl << endl;
	cout << "Name: " << this->name << endl << endl;
	for (Ingredient ingredient : this->ingredients)
	{
		cout << " => " << ingredient.getName() << endl;
	}
	cout << endl;
}
