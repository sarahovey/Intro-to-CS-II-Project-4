/**************************************
Author: Sara Hovey  
Date: 5/14/17
Description: Implementation file for the Medusa class. 
Contains virtual attack and defense functions
**************************************/

#include "Medusa.hpp"
#include "Creature.hpp"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

Medusa::Medusa(string name) : Creature(3, 8, name)
{

}

Medusa::~Medusa()
{

}

int Medusa::attack(Creature *opponent)
{
    // If a Medusa rolls a 12 in attack, then the target has looked her in the eyes and is turned to stone. 
    //The Medusa wins! If Medusa uses Glare on Harry Potter on his first life, then Harry Potter get back to life. 
    //If the Vampire's Charm ability activates versus Medusa's Glare, the Vampire's Charm trump the Glare.
    
    // Simulates 1 12-sided die
    int attack = (rand() % 6 + 1) + (rand() % 6 + 1);
    
    int damage;
    if (attack == 12)
    {
        // Glare sends in an attack arg
        // that is irrisistable by any creature
        // This implementation gives
        // Charm precidence over Glare
        damage = opponent->defend(1000);
		cout << "Medusa used GLARE!" << endl;
    }
    
    else
    {
        // Sends attack in as an arg
        // Returns the damage inflicted
        damage = opponent->defend(attack);
    }
    
    return damage;
}

int  Medusa::defend(int attack)
{
    // 1 d6
    int defense = rand() % 6 + 1;
    int damage = attack - defense;
    int total = damage - this->getArmor();

	if (total > 0)
	{
		int remainingStrength = this->getStrength() - total;
		this->setStrength(remainingStrength);
		return damage;
	}

	else
	{
		return 0;
	}  
   
}

/*****************
Rolls 2 d(n/2) where n= strength
********************/
void Medusa::heal()
{
	cout << "Medusa fed her snakes and has healed" << endl;

	// Resolves heal amount
	// Has potential to heal beyond their original amount
	int health = (rand() % 4 + 1) + (rand() % 4 + 1);
	int currentHealth = this->getStrength();
	int restore = health + currentHealth;
	if (restore > 8)
	{
		this->setStrength(8);
		return;
	}
	this->setStrength(restore);
}