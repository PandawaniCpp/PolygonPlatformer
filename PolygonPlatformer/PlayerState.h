#pragma once
#include <SFML/Graphics.hpp>
class Player;

namespace PlayerStateType {
    enum ID {
        ON_GROUND, FLYING
    };
}




class PlayerState {
public:

    
    virtual void update (Player* owner, sf::Time timePerFrame) {
    }
    virtual bool handleEvent (Player* owner, const sf::Event& event) {
        return true;
    };

    PlayerStateType::ID id;
};


class FlyingState :public PlayerState {
public:
    FlyingState ();
    virtual void update (Player* owner, sf::Time timePerFrame);
    bool handleEvent (Player* owner, const sf::Event& event);
};


class OnGroundState :public PlayerState {
public:
    OnGroundState ();
    virtual void update (Player* owner, sf::Time timePerFrame);
    bool handleEvent (Player* owner, const sf::Event& event);
};