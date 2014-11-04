#include <SFML/Graphics.hpp>

int main () {

    // Create a new game window
    sf::RenderWindow * gameWindow = new sf::RenderWindow (sf::VideoMode (1280, 720, 32), "Platformer", sf::Style::Close | sf::Style::Titlebar);
    gameWindow->setVisible (true);

    // Create a blue circle
    sf::CircleShape * circleShape = new sf::CircleShape (20.0f, 30U);
    circleShape->setFillColor (sf::Color::Blue);
    circleShape->setPosition (sf::Vector2<float> (50.0f, 50.0f));

    // Draw it on the screen
    gameWindow->draw (*circleShape);
    gameWindow->display ();

    while (1) {
    }

    return 0;
}