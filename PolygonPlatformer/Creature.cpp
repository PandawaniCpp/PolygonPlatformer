#include "Creature.h"

void Creature::damage(unsigned amount){
	hitPoints -= amount;
}

void Creature::heal(unsigned amount){
	hitPoints += amount;
}