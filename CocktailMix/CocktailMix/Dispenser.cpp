#include "stdafx.h"
#include "Dispenser.h"

#include <iostream>


Dispenser::Dispenser()
{
}


Dispenser::~Dispenser()
{
	delete this->ingredient;
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

void Dispenser::removeIngredient()
{
	this->ingredient->setName("free");
}
