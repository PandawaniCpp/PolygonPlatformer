
#include "Game.h"


Game::Game(){
	graphics.setWindowWidth(800);
	graphics.setWindowHeight(600);
	gameWindow.create(sf::VideoMode(graphics.getWindowWidth(), graphics.getWindowHeight()), "Platformer");
	gamePlayer.setRadius(40.f);
	gamePlayer.setPosition(400.f, 300.f);
	gamePlayer.setFillColor(sf::Color::Red);
}

Game::~Game()
{

}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	while (gameWindow.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (gameWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			break;

		case sf::Event::KeyReleased:
			break;

		case sf::Event::Closed:
			gameWindow.close();
			break;
		}
	}
}

void Game::update(sf::Time timePerFrame)
{

}

void Game::render()
{
	gameWindow.clear();
	gameWindow.draw(gamePlayer);
	gameWindow.display();
}