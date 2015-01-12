#pragma once
#include "Creature.h"
#include "EnemyBullet.h"
#include "NonPhysical.h"


class Pickup :public Creature {
public:
    Pickup (float x, float y,ObjectId::ID id);
    ~Pickup ();
    virtual void updateCurrent (sf::Time dt, b2World* world = nullptr);
    void preSolve (b2Contact* contact, SceneNode* anotherNode);
    void beginContact (SceneNode* anotherNode);
    void endContact (SceneNode* anotherNode);

    sf::Time lifespan;

};

