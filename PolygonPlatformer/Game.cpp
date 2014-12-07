#include <exception>
#include "Game.h"


Game::Game () : gameName ("Platformer"),
gameWindow (graphics.getVideoMode (), gameName, graphics.getWindowStyle ()), gamePlayer(new Player) {
    //gamePlayer.setRadius(40.f);
    //gamePlayer.setPosition(400.f, 300.f);
    //gamePlayer.setFillColor(sf::Color::Red);
    mRootNode.attachChild (gamePlayer);
    textures.load (Textures::PLAYER, "./textures/player.png");
    gamePlayer->setTexture (textures.get (Textures::PLAYER));
    gamePlayer->setPosition (300.f, 300.f);
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
                break;

            case sf::Event::KeyReleased:
                break;

            case sf::Event::Closed:
                gameWindow.close ();
                break;
        }
    }
}

void Game::update (sf::Time timePerFrame) {

}

void Game::render () {
    gameWindow.clear ();
    mRootNode.draw (gameWindow);
    gameWindow.display ();

    /* throw std::runtime_error ("LOL");
     throw std::runtime_error (errorHandler.getErrorMessage(ErrorHandler::FILE_NOT_FOUND));*/
}