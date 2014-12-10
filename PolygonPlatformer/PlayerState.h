#pragma once
#include <SFML/Graphics.hpp>
class Player;


class PlayerState {
public:
    virtual void update (Player* owner, sf::Time timePerFrame) {
    }
};


class JumpingState :public PlayerState {
    virtual void update (Player* owner, sf::Time timePerFrame);
};

class IdleState :public PlayerState {
    virtual void update (Player* owner, sf::Time timePerFrame);
};

class RunningState :public PlayerState {
    virtual void update (Player* owner, sf::Time timePerFrame);
};