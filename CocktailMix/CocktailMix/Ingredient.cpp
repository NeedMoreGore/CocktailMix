#include "stdafx.h"
#include "Ingredient.h"

#include <iostream>


Ingredient::Ingredient()
{
}


Ingredient::~Ingredient()
{
}

string Ingredient::getName()
{
	return this->name;
}

void Ingredient::setName(string name)
{
	this->name = name;
}