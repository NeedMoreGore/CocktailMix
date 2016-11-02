#pragma once

#include <string>
#include "Ingredient.h"
#include <vector>
#include <map>

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
	void setQuantity(Ingredient key, string value);
	string getQuantity(Ingredient i);

	void print();
private:
	string name;
	map<string, string> quantity; //no req
	vector<Ingredient> ingredients;
};

