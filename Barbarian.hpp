/********************************
Author: Sara Hovey  
Date: 5/14/17
Description:
********************************/

#ifndef BARBARIAN_HPP
#define BARBARIAN_HPP


#include "Creature.hpp"
#include <string>

using std::string;

class Barbarian : public Creature
{
  private:

  public:
  //Barbarian(int armor, int strength);
  Barbarian(std::string name);
  ~Barbarian();
  
  virtual int attack(Creature *opponent);
  virtual int defend(int attack);
  virtual void heal();
 
};

#endif