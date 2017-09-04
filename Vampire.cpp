/**************************************
Author: Sara Hovey  
Date: 5/14/17
Description: Implementation file for the Vampire class. 
Contains virtual attack and defense functions
**************************************/

#include "Vampire.hpp"
#include "Creature.hpp"
#include <iostream>
#include <string>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;
using std::string;

Vampire::Vampire(string name) : Creature(1, 18, name)
{

}

Vampire::~Vampire()
{

}

int Vampire::attack(Creature *opponent)
{
    // Simulates 1 12-sided die
    int attack = rand() % 12 + 1;
    
    // Sends attack in as an arg
    // Returns the damage inflicted
    int damage = opponent->defend(attack);
    return damage;
    
}

/******************************************
Modified defense with the Charm trait 
Charm: 
Vampires can charm an opponent into not attacking. 
For a given attack there is a 50% chance that
their opponent does not actually attack them.
****************************************/
int  Vampire::defend(int attack)
{
    int charm = rand() % 2+ 1;
    int defense, total, damage, remainingStrength;
    
    // In this implementation, 1 is the condition
    // for the opponent to attack
    if(charm == 1)
    {
        defense = rand() % 6 + 1;
        damage = attack - defense;
        total = damage - this->getArmor();

		if (total > 0)
		{
			remainingStrength = this->getStrength() - total;
			this->setStrength(remainingStrength);

			return damage;

		}

		else
		{
			return 0;
		}
    }
    
    // In this implementation, 2 is the condition
    // for the opponent to  be "charmed"
    if(charm == 2)
    {
        // Nothing happens
		cout << "Vampire has charmed their attacker!" << endl;
        return 0;
    }

	else
	{
		return 0;
	}
    
}

void Vampire::heal()
{
	cout << "The vampire rested in their coffin" << endl;

	// Resolves heal amount
	// Has potential to heal beyond their original amount
	int health = (rand() % 9 + 1) + (rand() % 9 + 1);
	int currentHealth = this->getStrength();
	int restore = health + currentHealth;
	if (restore > 18)
	{
		this->setStrength(18);
		return;
	}
	this->setStrength(restore);
}