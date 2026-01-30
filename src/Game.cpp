#include "Game.h"

#include "Constants.h"

using namespace Constants;

Game::Game() : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), WINDOW_NAME) {};

void Game::run() {
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
                 sf::Keyboard::isKeyPressed(sf::Keyboard::Q))) {
                window.close();
            }
        }

        sf::RectangleShape middleLine(sf::Vector2f(window.getSize().x * 0.01, window.getSize().y));
        middleLine.setPosition(sf::Vector2f(window.getSize().x / 2, 0));

        window.draw(middleLine);

        window.display();
    }
}