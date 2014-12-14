#include "Player.h"

Player::Player () :currentState (new IdleState) {
}

void Player::updateCurrent (sf::Time dt) {
    currentState->update (this, dt);
}