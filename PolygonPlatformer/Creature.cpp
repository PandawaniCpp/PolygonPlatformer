#include "Creature.h"

SceneNode* Creature::currentPlayer = nullptr;



void Creature::damage (float amount) {
    currentHP -= amount;
}

void Creature::heal (float amount) {
	currentHP += amount;
}

Creature::Creature () {
	maxHP = 10;
	currentHP = 10;
}


