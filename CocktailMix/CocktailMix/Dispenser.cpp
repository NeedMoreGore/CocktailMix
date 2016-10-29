#include "stdafx.h"
#include "Dispenser.h"


Dispenser::Dispenser()
{
}


Dispenser::~Dispenser()
{
}

void Dispenser::setNumber(int number)
{
	this->number = number;
}

int Dispenser::getNumber()
{
	return this->number;
}

void Dispenser::setIngredient(Ingredient &ingredient)
{
	this->ingredient = &ingredient;
}
Ingredient Dispenser::getIngredient()
{
	return *ingredient;
}
