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
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        std::cout << mousePosition.x << " - " << mousePosition.y << '\n';

        handleInput();

        sf::Time dtTime = clock.restart();
        float dt = dtTime.asSeconds();
        paddlePlayer2.update(dt);

        ball.update(dt);

        if (checkCollisions(paddlePlayer1) || checkCollisions(paddlePlayer2)) {
            ball.setVelocity(sf::Vector2f(-ball.getVelocity().x, 0.f));
        }

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

    sf::Vector2f velocity(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        velocity.y = -C::PADDLE_SPEED;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        velocity.y = +C::PADDLE_SPEED;
    }
    paddlePlayer2.setVelocity(velocity);
}

bool Game::checkCollisions(const Paddle& paddle) {
    float ballX1 = ball.getPosition().x;
    float ballX2 = ball.getPosition().x + C::BALL_WIDTH;
    float ballY1 = ball.getPosition().y;
    float ballY2 = ball.getPosition().y + C::BALL_HEIGHT;

    float paddleX1 = paddle.getPosition().x;
    float paddleX2 = paddle.getPosition().x + C::PADDLE_WIDTH;
    float paddleY1 = paddle.getPosition().y;
    float paddleY2 = paddle.getPosition().y + C::PADDLE_HEIGHT;

    if (ballX1 >= paddleX2 || ballX2 <= paddleX1 || ballY1 >= paddleY2 || ballY2 <= paddleY1) {
        return false;
    }
    return true;
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