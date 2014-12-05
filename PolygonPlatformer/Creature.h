#include "Entity.h"

class Creature :public Entity{

public:
	Creature();

	void heal(unsigned amount);

	void damage(unsigned amount);

	virtual void drawCurrent(sf::RenderTarget& target,
		sf::RenderStates states) const;


protected:
	int hitPoints;

private:
	sf::Sprite mSprite;

};