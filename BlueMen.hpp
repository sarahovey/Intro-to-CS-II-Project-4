/********************************
Author: Sara Hovey  
Date: 5/14/17
Description:
********************************/

#ifndef BLUEMEN_HPP
#define BLUEMEN_HPP


#include "Creature.hpp"
#include "Creature.hpp"
#include <string>

using std::string;

class BlueMen : public Creature
{
  private:
  

  public:
  //BlueMen(int armor, int strength);
  BlueMen(std::string name);
  ~BlueMen();
  
  virtual int attack(Creature *opponent);
  virtual int defend(int attack);
  virtual void heal();
 
  
};

#endif