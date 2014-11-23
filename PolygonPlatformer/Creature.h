#include "Entity.h"

class Creature :public Entity{

public:
	void heal(unsigned amount);

	void damage(unsigned amount);

protected:
	int hitPoints;

};