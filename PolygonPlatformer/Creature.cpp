#include "Creature.h"

SceneNode* Creature::currentPlayer = nullptr;



void Creature::damage (unsigned amount) {
    currentHP -= amount;
}

void Creature::heal (unsigned amount) {
	currentHP += amount;
}

Creature::Creature () {
	maxHP = 10;
	currentHP = 10;
}


