#include "Creature.h"
#include "PlayerState.h"
#pragma once

class Player :public Creature {
public:
    PlayerState *currentState;
    Player ();
    virtual void updateCurrent (sf::Time dt);
};
