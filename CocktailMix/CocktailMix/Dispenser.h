	#pragma once
	

#include "Ingredient.h"

using namespace std;

class Dispenser
{
	public:
		Dispenser();
		~Dispenser();

		void setNumber(int number);
		int getNumber();
		void setIngredient(Ingredient &ingredient);
		void removeIngredient();
		Ingredient getIngredient();

	private:
		unsigned int number;
		Ingredient *ingredient;
};

