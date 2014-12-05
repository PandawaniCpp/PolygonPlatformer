#include "SceneNode.h"

class Entity : public SceneNode{

public:
	Entity();

	void setPosition(float x, float y);

	void setPosition(sf::Vector2f position);

	sf::Vector2f getPosition();
protected:
	sf::Vector2f mPosition;
};