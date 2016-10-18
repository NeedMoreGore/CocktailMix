	#pragma once

	#include <string>

	using namespace std;

//Req 05
	class Ingredient
	{
	public:
		Ingredient();
		~Ingredient();
		string getName();
		void setName(string name);
	private:
		string name;
	};

