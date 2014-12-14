#include "PlayerState.h"
#include "Player.h"


FlyingState::FlyingState() {
    id = PlayerStateType::FLYING;
}

OnGroundState::OnGroundState () {
    id = PlayerStateType::ON_GROUND;
}


void FlyingState::update (Player* owner, sf::Time timePerFrame) {

}


void OnGroundState::update (Player* owner, sf::Time timePerFrame) {

}


bool FlyingState::handleEvent (Player* owner, const sf::Event& event) {
    switch (event.type) {
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::W)
                owner->isJumping = true;
            if (event.key.code == sf::Keyboard::A)
                owner->isMovingLeft = true;
            if (event.key.code == sf::Keyboard::D)
                owner->isMovingRight = true;
            break;

        case sf::Event::KeyReleased:
            if (event.key.code == sf::Keyboard::W)
                owner->isJumping = false;
            if (event.key.code == sf::Keyboard::A)
                owner->isMovingLeft = false;
            if (event.key.code == sf::Keyboard::D)
                owner->isMovingRight = false;
            break;
    }
    return true;
}

bool OnGroundState::handleEvent (Player* owner, const sf::Event& event) {
    switch (event.type) {
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::W)
                owner->isJumping = true;
            if (event.key.code == sf::Keyboard::A)
                owner->isMovingLeft = true;
            if (event.key.code == sf::Keyboard::D)
                owner->isMovingRight = true;
            break;

        case sf::Event::KeyReleased:
            if (event.key.code == sf::Keyboard::W)
                owner->isJumping = false;
            if (event.key.code == sf::Keyboard::A)
                owner->isMovingLeft = false;
            if (event.key.code == sf::Keyboard::D)
                owner->isMovingRight = false;
            break;
    }
    return true;
}