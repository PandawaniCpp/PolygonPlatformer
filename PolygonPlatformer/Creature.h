#pragma once
#include "Entity.h"

class Creature :public Entity {

public:
    Creature ();

    void heal (float amount);

    virtual void damage (float amount);

	static SceneNode* currentPlayer;
	float maxHP;
	float currentHP;



};