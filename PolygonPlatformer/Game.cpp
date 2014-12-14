#include <exception>
#include "Game.h"


Game::Game() : gameName("Platformer"), mStateStack(),
gameWindow (graphics.getVideoMode (), gameName, graphics.getWindowStyle (), graphics.getContextSettings()) {
    //Settig basic window options
	gameWindow.setVerticalSyncEnabled(graphics.getVsync());
	gameWindow.setMouseCursorVisible(false);
	gameWindow.setIcon(window_icon.width, window_icon.height, window_icon.pixel_data);

	//States
	mStateStack.registerState<MenuState>(States::MENU);   
	mStateStack.registerState<GameState>(States::GAME);
	mStateStack.pushState(States::GAME);
	mStateStack.applyPendingChanges();

	//Player
    /*mRootNode.attachChild (gamePlayer);
    textures.load (Textures::PLAYER, "./textures/player.png");
    gamePlayer->setTexture (textures.get (Textures::PLAYER));
    gamePlayer->setPosition (300.f, 300.f);*/
}

Game::~Game () {

}

void Game::run () {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time timePerFrame = sf::seconds (1.f / 60.f);

    while (gameWindow.isOpen ()) {
        processEvents ();
        timeSinceLastUpdate += clock.restart ();
        while (timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;
            processEvents ();
            update (timePerFrame);
        }
        render ();
    }
}

void Game::processEvents () {
    sf::Event event;
    while (gameWindow.pollEvent (event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
				mStateStack.handleEvent(event);
                break;

            case sf::Event::KeyReleased:
				mStateStack.handleEvent(event);
                break;

            case sf::Event::Closed:
                gameWindow.close ();
                break;
        }
    }
}

void Game::update (sf::Time timePerFrame) {
	mStateStack.update(timePerFrame);
}

void Game::render () {
    gameWindow.clear ();
	mStateStack.draw(gameWindow);
    //mRootNode.draw (gameWindow);
    gameWindow.display ();

    /* throw std::runtime_error ("LOL");
     throw std::runtime_error (errorHandler.getErrorMessage(ErrorHandler::FILE_NOT_FOUND));*/
}