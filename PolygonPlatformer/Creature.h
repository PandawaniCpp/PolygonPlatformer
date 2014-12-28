#pragma once
#include "Entity.h"

class Creature :public Entity {

public:
    Creature ();

    void heal (unsigned amount);

    void damage (unsigned amount);

	static SceneNode* currentPlayer;
protected:
    float maxHP;
	float currentHP;

};