#include "Entity.h"

class Creature :public Entity {

public:
    Creature ();

    void heal (unsigned amount);

    void damage (unsigned amount);


protected:
    float maxHP;
	float currentHP;

};