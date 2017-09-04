/**************************************
Author: Sara Hovey  
Date: 5/14/17
Description:
**************************************/

#include "Creature.hpp"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

Creature::Creature(int armor, int strength, string name)
{
	this->name = name;
	this->armor = armor;
	this->strength = strength;
}

Creature::~Creature()
{

}

int Creature::getArmor()
{
    return armor;
}

int Creature::getStrength()
{
    return strength;
}

std::string Creature::getName()
{
	return name;
}

void Creature::setStrength(int strength)
{
    this->strength = strength;
}

int Creature::attack(Creature *opponent)
{
    cout << "I can't attack from here!" << endl;
    return 0;
}

int  Creature::defend(int attack)
{
    cout<< "I can't defend from here! " << endl;
    return 0;
}


/****************************
Rolls 2 d(n/2) where n= strength
******************************/
void Creature::heal()
{
	cout << "I can't heal from here!" << endl;
}