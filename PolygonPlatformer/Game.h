#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics.h"
#include "ErrorHandler.h"
#include "SceneNode.h"
#include "TextureHolder.h"
#include "Player.h"
#include "./textures/window_icon.cpp"



class Game {

public:
    Game ();

    virtual ~Game ();

    void run ();

private:

    void processEvents ();

    void update (sf::Time timePerFrame);

    void render ();

private:

    Graphics graphics;

    ErrorHandler errorHandler;

    std::string gameName;

    sf::RenderWindow gameWindow;

    Player::Ptr gamePlayer;

    TextureHolder textures;

    SceneNode mRootNode;
};

