#pragma once
#include <SFML/Graphics.hpp>

class Game
{
private:

	sf::RenderWindow gameWindow;

	sf::CircleShape gamePlayer;

public:
	Game();

	virtual ~Game();

	void run();

private:

	void processEvents();

	void update(sf::Time timePerFrame);

	void render();
};

