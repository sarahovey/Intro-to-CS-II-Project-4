/********************************
Author: Sara Hovey  
Date: 5/13/17
Description:
********************************/

#ifndef CREATURE_HPP
#define CREATURE_HPP
#include <string>

using std::string;

class Creature
{
  private:
  std::string name;

  protected:
  int armor;
  int strength;

  public:
  Creature(int armor, int strength, std::string name);
  virtual ~Creature();

  int getArmor();
  int getStrength();
  std::string getName();
  void setStrength(int strength);
  virtual int attack(Creature *opponent);
  virtual int defend(int attack);
  virtual void heal();
  
};

#endif