#include "SceneNode.h"
#include <Box2D/Box2D.h>
class Entity : public SceneNode {

public:
    Entity ();

    /*void setPosition (float x, float y);

    void setPosition (sf::Vector2f position);*/

    sf::Vector2f getPosition ();

    
protected:
    sf::Vector2f mPosition;
};