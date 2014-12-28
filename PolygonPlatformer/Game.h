#pragma once
#include <SFML/Graphics.hpp>

//Basic core
#include "Graphics.h"
#include "ErrorHandler.h"
#include "SceneNode.h"
#include "TextureHolder.h"
#include "Player.h"

//States
#include "StateStack.h"
#include "MenuState.h"
#include "GameState.h"
#include "TitleState.h"
#include "PauseState.h"

// enumerators
#include "ResourcesID.h"

//Icon
#include "./textures/window_icon.cpp"



class Game {
	friend class GameState;
	friend class TitleState;
	friend class MenuState;
	friend class LoadState;
	friend class PauseState;
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

    //Player::Ptr gamePlayer;

    //TextureHolder textures;

    //SceneNode mRootNode;

	StateStack mStateStack;
};

