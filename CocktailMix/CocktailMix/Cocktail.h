#pragma once

#include <string>
#include "Ingredient.h"
#include <vector>

using namespace std;

class Cocktail
{
public:
	Cocktail();
	~Cocktail();

	void setName(string name);
	string getName();
	void setIngredients(vector<Ingredient>);
	vector<Ingredient> getIngredients();

	void print();
private:
	string name;
	vector<Ingredient> ingredients;
};

