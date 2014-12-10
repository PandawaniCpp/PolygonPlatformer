#include "Player.h"

Player::Player () :currentState (new IdleState) {
}

void Player::update (sf::Time timePerFrame) {
    currentState->update (this, timePerFrame);
}