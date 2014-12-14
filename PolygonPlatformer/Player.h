#include "Creature.h"
#include "PlayerState.h"
#include <Box2D/Box2D.h>

#pragma once

class Player :public Creature {
public:
    PlayerState *currentState;
    Player ();
    virtual void updateCurrent (sf::Time dt, b2World* world = nullptr);
    
};
