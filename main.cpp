/**************************************
Author: Sara Hovey  
Date: 5/14/17
Description: Implementation file for the Vampire class. 
Contains virtual attack and defense functions
**************************************/

#include "Creature.hpp"
#include "HarryPotter.hpp"
#include "Medusa.hpp"
#include "Vampire.hpp"
#include "Barbarian.hpp"
#include "BlueMen.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <climits>

using std::cin;
using std::cout;
using std::endl;
using std::string;

// New template struct
struct node
{
	Creature *data;
	node* next;
	node* prev;

	node(Creature *c) : data(c) {}
};

void tournament(struct node** h1, struct node** h2, struct node** h3, struct node** t1, struct node** t2);
int fight(Creature *f1, Creature *f2);
node* monsterFactory(int team, int iteration, struct node* h);
bool validateInt(int data, int min, int max);
node* addToHead(struct node* h, Creature *creature);
node* addToTail(struct node* t, Creature *creature);
node* deleteHead(struct node * h);
node* deleteTail(struct node * t);


int main()
{
	// For this version,

	// in fight functions, the opponents are referred to as f1 and f2
	// in the context of all of them, they are referred to by their user-given name

	bool done = false;

	while (done == false)
	{
		//Setting up the lists
		node* h1 = NULL;
		node* h2 = NULL;
		node* h3 = NULL;
		node* t1 = NULL;
		node* t2 = NULL;

		bool valid1 = false;
		int tourneyNum;
		while (valid1 == false)
		{
			cout << "Welcome to the fite tournament" << endl;
			cout << "How many fighters should be on either side? " << endl;
			cout << "Enter a number between 1 and 30 inclusive " << endl;

			if (cin >> tourneyNum)
			{
				valid1 = validateInt(tourneyNum, 1, 30);
			}

			else
			{
				cout << "Please enter a valid integer" << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
		}

		cout << "Let's visit the Monster factory to make Team 1" << endl;
		// Making team 1
		for (int i = 0; i < tourneyNum; i++)
		{
			
			cout << "" << endl;
			cout << "*******" << endl;
			cout << "" << endl;

			// Call monsterFactory with data for team 1, and the iteration the loop is on
			h1 = monsterFactory(1, i, h1);
			if (t1 == NULL) {
				t1 = h1;
			}
		}

		cout << "" << endl;
		cout << "*******" << endl;
		cout << "" << endl;

		// Making team 2
		cout << "Let's visit the Monster factory to make Team 2" << endl;
		for (int i = 0; i < tourneyNum; i++)
		{
		
			cout << "" << endl;
			cout << "*******" << endl;
			cout << "" << endl;

			// Call monsterFactory with data for team 2, and the iteration the loop is on
			h2 = monsterFactory(2, i, h2);
			if (t2 == NULL) {
				t2 = h2;
			}
		}

		cout << "Let's begin the match" << endl;
		cout << "" << endl;
		cout << "*******" << endl;
		cout << "" << endl;

		cout << "Calling tournament()" << endl;

		// Call tournament() while the teams still have fighters
		while (h1 != NULL && h2 != NULL)
		{
			tournament(&h1, &h2, &h3, &t1, &t2);
		}
		
		if (h1 == NULL)
		{
			cout << "Team 1 has run out of fighters!" << endl;
		}

		else if (h2 == NULL)
		{
			cout << "Team 2 has run out of fighters!" << endl;
		}

		else
		{
			cout << "Uh, well" << endl;
		}


		// delete all this dang memory
		// Delete everything from all 3 lists

		// Delete all the nodes and all the fighters stored in the nodes
		// Team 1
		
		while (h1 != NULL)
		{
			node* temp = h1->next;
			delete h1->data;
			delete h1;
			h1 = temp;
		}

		// Team 2
		while (h2 != NULL)
		{
			node* temp = h2->next;
			delete h2->data;
			delete h2;
			h2 = temp;
		}

		// Team 3
		while (h3 != NULL)
		{
			node* temp = h3->prev;
			delete h3->data;
			delete h3;
			h3 = temp;
		}

		// Check for being finished playing
		bool finished = false;
		int playAgain;
		while (finished == false)
		{
			cout << "Play again?" << endl;
			cout << "1. Yes" << endl;
			cout << "2. No" << endl;

			if (cin >> playAgain)
			{
				// Validate range
				finished = validateInt(playAgain, 1, 2);

			}
			else
			{
				cout << "Please select an option" << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}

			if (playAgain == 1)
			{
				done = false;
			}

			else if (playAgain == 2)
			{
				done = true;
			}
		}
	}

	return 0;
}

/*******************
Fight functions
*********************/
void tournament(struct node** h1, struct node** h2, struct node** h3, struct node** t1, struct node **t2)
{
	//h1->data holds a Creature object
	Creature *f1 = (*h1)->data;
	Creature *f2 = (*h2)->data;

	// call fight() with the heads of each team
	int winner = fight(f1, f2);

	// When a winner and a loser win/lose, their strength needs to be preserved
	// ie, if a character takes damage, but wins, they need to get to the back 
	// of the list with the damage they took + whatever they healed
	if (winner == 1)
	{
		//Handle winner
		//Put winner at the back of the list
		*t1 = addToTail(*t1, f1);
		*h1 = deleteHead(*h1);

		//Handle loser
		//Remove loser from their list
		//Pass loser into addHead() with the head of
		//The third list, such that the losing creature
		//Becomes a new node that replaces the head
		*h2 = deleteHead(*h2);
		if (*h2 == NULL) {
			*t2 = NULL;
		}
		*h3 = addToHead(*h3, f2);

		f1->heal();
		cout << "The winner of this match is Team 1's " << f1->getName() << endl;
	}

	else if (winner == 2)
	{
		//Handle winner
		*t2 = addToTail(*t2, f2);
		*h2 = deleteHead(*h2);

		//Handle loser
		*h1 = deleteHead(*h1);
		if (*h1 == NULL) {
			*t1 = NULL;
		}
		*h3 = addToHead(*h3, f1);

		f2->heal();
		cout << "The winner of this match is Team 2's " << f2->getName() << endl;
	}

	else
	{
		cout << "Unknown winner" << endl;
	}

}

int fight(Creature *f1, Creature *f2)
{
	// Will return how much damage the opponent took
	// They need to take turns attacking each other, but 
	// also a dead character shouldn't fight


	// Random start
	int randTurn = rand() % 2 + 1;

	//f1 goes first in a fight to KO
	if (randTurn == 1)
	{
		// This condition checks for a dead character
		while (f1->getStrength() > 0 && f2->getStrength() > 0)
		{
			cout << "Fighter 1 is attacking" << endl;
			cout << "Fighter 1 did " << f1->attack(f2) << " damage" << endl;
			cout << "After effects and armor, the opponent fighter 2 has " << f2->getStrength() << " health left" << endl;
			cout << "" << endl;

			if (f2->getStrength() > 0 && f1->getStrength() > 0)
			{
				// Fight
				cout << "Fighter 2 is attacking" << endl;
				cout << "Fighter 2 did " << f2->attack(f1) << " damage" << endl;
				cout << "After effects and armor, the opponent fighter 1 has " << f1->getStrength() << " health left" << endl;
				cout << "" << endl;

			}
		}
	}

	else if (randTurn == 2)
	{
		// This condition checks for a dead character
		while (f1->getStrength() > 0 && f2->getStrength() > 0)
		{

			cout << "Fighter 2 is attacking" << endl;
			cout << "Fighter 2 did " << f2->attack(f1) << " damage" << endl;
			cout << "After effects and armor, the opponent fighter 1 has " << f1->getStrength() << " health left" << endl;
			cout << "" << endl;

			if (f2->getStrength() > 0 && f1->getStrength() > 0)
			{
				// Fight player 1
				cout << "Fighter 1 is attacking" << endl;
				cout << "Fighter 1 did " << f1->attack(f2) << " damage" << endl;
				cout << "After effects and armor, the opponent fighter 2 has " << f2->getStrength() << " health left" << endl;
				cout << "" << endl;

			}
		}
	}

	//Checking win

	if (f1->getStrength() <= 0)
	{
		cout << "Fighter 2 has won!" << endl;
		cout << "*****************" << endl;
		cout << "" << endl;

		return 1;
	}

	else if (f2->getStrength() <= 0)
	{
		cout << "Fighter 1 has won!" << endl;
		cout << "*****************" << endl;
		cout << "" << endl;

		return 2;
	}

	else
	{
		throw "Logic error, neither fighter has lost";
	}

}


/****************************
Helper functions!
*****************************/

/****************************
Handles the creation of new fighters
Names them 
Creates the new object of the right subclass
Adds them to the appropriate team
Returns a pointer to the node that represents them
*****************************/
node* monsterFactory(int team, int iteration, struct node* h)
{
	// Name the character
	string name;

	cout << "Choose a name for your fighter!" << endl;
	cin >> name;

	//Create new Creature
	Creature *creature;

	// Get character type
	bool valid = false;
	int input;
	while (valid == false)
	{
		cout << "Pick fighter #"<< iteration + 1 << endl;
		cout << "1. Vampire" << endl;
		cout << "2. Barbarian" << endl;
		cout << "3. BlueMen" << endl;
		cout << "4. Medusa" << endl;
		cout << "5. HarryPotter" << endl;

		if (cin >> input)
		{
			// Validate range
			valid = validateInt(input, 1, 5);

		}
		else
		{
			cout << "Please select an option" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	}

	// Vampire
	if (input == 1)
	{
		creature = new Vampire(name);
		cout << "Fighter " << iteration + 1 << ", " << name << " is a Vampire" << endl;
		cout << " " << endl;
	}

	// Barbarian
	else if (input == 2)
	{
		creature = new Barbarian(name);
		cout << "Fighter " << iteration + 1 << ", " << name << " is a Barbarian" << endl;
		cout << " " << endl;
	}

	// BlueMen
	else if (input == 3)
	{
		creature = new BlueMen(name);
		cout << "Fighter " << iteration + 1 << ", " << name << " is a BlueMen" << endl;
		cout << " " << endl;
	}
	//Medusa
	else if (input == 4)
	{
		creature = new Medusa(name);
		cout << "Fighter " << iteration + 1 << ", " << name << " is a Medusa" << endl;
		cout << " " << endl;
		
	}
	//HarryPotter
	else if (input == 5)
	{
		creature = new HarryPotter(name);
		cout << "Fighter " << iteration + 1<< ", " << name << " is a Harry Potter" << endl;
		cout << " " << endl;
	}
	
	else
	{
		cout << "Unknown number" << endl;
	}

	if (team == 1)
	{
		// add to team 1's list
		h = addToHead(h, creature);
		cout << name << " has been added to team 1!" << endl;
		cout << "" << endl;
		cout << "*******" << endl;
		cout << "" << endl;

		return h;
	}

	else if (team == 2)
	{
		// Add to team 2's list
		h = addToHead(h, creature);
		cout << name << " has been added to team 2!" << endl;
		cout << "" << endl;
		cout << "*******" << endl;
		cout << "" << endl;

		return h;
	}

	else
	{
		throw "Invalid team";
	}
}

bool validateInt(int data, int min, int max)
{
	if (data<min || data > max)
	{
		cout << "Please enter a number between " << min << " and " << max << endl;
		return false;
	}

	return true;
}

node* addToHead(struct node* h, Creature *creature)
{
	
	// Make a new node
	 node *n = new node(creature);

	// Set n->next as the head
	n->next = h;
	// Because it's the head, the prev ptr is nul
	n->prev = NULL;

	// Link the new head node to the former
	// head node
	if (h != NULL)
	{
		h->prev = n;
	}

	/*cout << "New node added to head" << endl;
	cout << "" << endl;
	cout << "*******" << endl;
	cout << "" << endl;
*/

	return n;
}


node* addToTail(struct node* t, Creature *creature)
{
	// Make a new node
	node* n = new node(creature);

	// The ->next is NULL, bc it's last
	n->next = NULL;

	// Point at the current tail
	n->prev = t;

	if (t != NULL)
	{
		t->next = n;
	}

	//In the case of a 1 node list, do I need to 
	cout << "New node added to tail" << endl;
	cout << "" << endl;
	cout << "*******" << endl;
	cout << "" << endl;

	return n;
}

node* deleteHead(struct node * h)
{
	if (h == NULL)
	{
		cout << "There's nothing here!" << endl;
		cout << "" << endl;
		cout << "" << endl;
		cout << "*******" << endl;
		cout << "" << endl;

		return h;
	}

	else
	{
		node* temp = h->next;

		delete h;

		if (temp != NULL) {
			temp->prev = NULL;
		}

		cout << "Node deleted from head" << endl;
		cout << "" << endl;
		cout << "*******" << endl;
		cout << "" << endl;


		return temp;
	}

}


node* deleteTail(struct node * t)
{
	// Last node was passed in
	// Set the former 2nd to last's next node to NULL
	// Since it's going to be the last node

	if (t == NULL)
	{
		cout << "There's nothing here!" << endl;
		cout << "" << endl;
		return t;
	}

	else
	{
		node* temp = t->prev;

		delete t;

		if (temp != NULL) {
			temp->next = NULL;
		}

		cout << "Node deleted from tail" << endl;

		return temp;
	}
}

