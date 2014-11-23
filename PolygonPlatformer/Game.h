#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics.h"

class Game{

public:
	Game();

	virtual ~Game();

	void run();

private:

	void processEvents();

	void update(sf::Time timePerFrame);

	void render();

private:

	sf::RenderWindow gameWindow;

	sf::CircleShape gamePlayer;

	Graphics graphics;
};

