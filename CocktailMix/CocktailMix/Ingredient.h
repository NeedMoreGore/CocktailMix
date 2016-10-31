#pragma once

#include <string>

using namespace std;

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

