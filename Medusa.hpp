/********************************
Author: Sara Hovey  
Date: 5/14/17
Description:
********************************/

#ifndef MEDUSA_HPP
#define MEDUSA_HPP

#include "Creature.hpp"
#include "Creature.hpp"
//#include <string>

//using std::string;

class Medusa : public Creature
{
  private:
  

  public:
  //Medusa(int armor, int strength);
  
  Medusa(string name);
  ~Medusa();

  virtual int attack(Creature *opponent);
  virtual int defend(int attack);
  virtual void heal();
 
  
};

#endif