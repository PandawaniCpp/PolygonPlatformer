#include "Entity.h"

class Creature :public Entity {

public:
    Creature ();

    void heal (unsigned amount);

    void damage (unsigned amount);


protected:
    int hitPoints;

};