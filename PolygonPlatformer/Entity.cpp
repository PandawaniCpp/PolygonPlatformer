#include "Entity.h"

Entity::Entity () {
    mPosition.x = 0.f;
    mPosition.y = 0.f;
}

/*void Entity::setPosition (sf::Vector2f position) {
    mPosition = position;
}

void Entity::setPosition (float x, float y) {
    mPosition.x = x;
    mPosition.y = y;
}*/

sf::Vector2f Entity::getPosition () {
    return mPosition;
}