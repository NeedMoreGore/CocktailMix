	#pragma once

	using namespace std;

	#include <string>
	#include "Ingredient.h"
	#include <vector>
//Req 07
	class Cocktail
	{
	public:
		Cocktail();
		~Cocktail();
//Req 08
		void setName(string name);
		string getName();
		void setIngredients(vector<Ingredient>);
		vector<Ingredient> getIngredients();

		void print();
	private:
		string name;
		vector<Ingredient> ingredients;
	};

