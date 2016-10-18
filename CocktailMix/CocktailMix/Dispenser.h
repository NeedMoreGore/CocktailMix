	#pragma once
	
	using namespace std;

	#include "Ingredient.h"
//Req06
	class Dispenser
	{
		public:
			Dispenser();
			~Dispenser();

			void setNumber(int number);
			int getNumber();
			void setIngredient(Ingredient &ingredient);
			Ingredient getIngredient();

		private:
			unsigned int number;
			Ingredient *ingredient;
	};

