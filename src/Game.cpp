#include "Game.h"

#include <iostream>

#include "Constants.h"

namespace C = Constants;

Game::Game()
    : window{sf::VideoMode(C::WINDOW_WIDTH, C::WINDOW_HEIGHT), C::WINDOW_NAME},
      ball{},
      paddlePlayer1{sf::Vector2f(C::PADDLE_P1_X, C::PADDLE_P1_Y)},
      paddlePlayer2{sf::Vector2f(C::PADDLE_P2_X, C::PADDLE_P2_Y)},
      scorePlayer1{sf::Vector2f(C::SCORE_P1_X, C::SCORE_P1_Y), true},
      scorePlayer2{sf::Vector2f(C::SCORE_P2_X, C::SCORE_P2_Y), false} {};

void Game::run() {
    while (window.isOpen()) {
        sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        std::cout << mousePosition.x << " - " << mousePosition.y << '\n';

        handleInput();

        render();
    }
}

void Game::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed ||
            (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
             sf::Keyboard::isKeyPressed(sf::Keyboard::Q))) {
            window.close();
        }
    }
}

void Game::render() {
    window.clear();

    sf::VertexArray middleLine(sf::Lines, C::NO_LINES);
    for (int i = 0; i < C::NO_LINES; i++) {
        middleLine[i].position = sf::Vector2f(C::WINDOW_WIDTH / 2, i * C::LINE_LENGTH);
    }

    window.draw(ball);
    window.draw(paddlePlayer1);
    window.draw(paddlePlayer2);
    window.draw(middleLine);
    window.draw(scorePlayer1);
    window.draw(scorePlayer2);

    window.display();
}