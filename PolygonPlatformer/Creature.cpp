#include "Creature.h"

void Creature::damage(unsigned amount){
	hitPoints -= amount;
}

void Creature::heal(unsigned amount)
{
	hitPoints += amount;
}

Creature::Creature()
{
	hitPoints = 10; 
}


void Creature::drawCurrent(sf::RenderTarget& target,sf::RenderStates states) const
{
	target.draw(mSprite, states);
}