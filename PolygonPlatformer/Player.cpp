#include "Player.h"
#define PIXELTOMETER (1.f/10.f)

Player::Player () :currentState (new IdleState) {
}

void Player::updateCurrent (sf::Time dt, b2World* world) {
    setPosition (myBody->GetPosition ().x / PIXELTOMETER, myBody->GetPosition ().y / PIXELTOMETER);
    currentState->update (this, dt);
}