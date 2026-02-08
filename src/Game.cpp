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
        handleInput();
        updateHardCodedAI();

        sf::Time dtTime = clock.restart();
        float dt = dtTime.asSeconds();

        paddlePlayer1.update(dt);
        paddlePlayer2.update(dt);

        ball.update(dt);

        if (ball.getVelocity().x < 0) {
            auto [collisionType, penetration] = checkPaddleCollision(paddlePlayer1);
            if (collisionType != C::CollisionType::None) {
                ball.collideWithPaddle(paddlePlayer1, penetration);
            }

        } else if (ball.getVelocity().x > 0) {
            auto [collisionType, penetration] = checkPaddleCollision(paddlePlayer2);
            if (collisionType != C::CollisionType::None) {
                ball.collideWithPaddle(paddlePlayer2, penetration);
            }
        }

        auto [collisionType, penetration] = checkWallCollision();

        if (collisionType == C::CollisionType::Left) {
            scorePlayer2.increment();

        } else if (collisionType == C::CollisionType::Right) {
            scorePlayer1.increment();
        }

        if (collisionType != C::CollisionType::None) {
            ball.collideWithWall(collisionType, penetration);
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

void Game::updateHardCodedAI() {
    float paddleCenterY = paddlePlayer1.getPosition().y + (C::PADDLE_HEIGHT / 2.f);
    float ballCenterY = ball.getPosition().y + (C::BALL_HEIGHT / 2.f);

    sf::Vector2f velocity{0.f, 0.f};
    if (ballCenterY < paddleCenterY - C::DEAD_ZONE) {
        velocity.y = -C::AI_PADDLE_SPEED;
    } else if (ballCenterY > paddleCenterY + C::DEAD_ZONE) {
        velocity.y = C::AI_PADDLE_SPEED;
    }
    paddlePlayer1.setVelocity(velocity);
}

std::pair<C::CollisionType, float> Game::checkPaddleCollision(const Paddle& paddle) {
    float ballX1 = ball.getPosition().x;
    float ballX2 = ball.getPosition().x + C::BALL_WIDTH;
    float ballY1 = ball.getPosition().y;
    float ballY2 = ball.getPosition().y + C::BALL_HEIGHT;

    float paddleX1 = paddle.getPosition().x;
    float paddleX2 = paddle.getPosition().x + C::PADDLE_WIDTH;
    float paddleY1 = paddle.getPosition().y;
    float paddleY2 = paddle.getPosition().y + C::PADDLE_HEIGHT;

    if (ballX1 >= paddleX2 || ballX2 <= paddleX1 || ballY1 >= paddleY2 || ballY2 <= paddleY1) {
        return {C::CollisionType::None, 0.f};
    }

    float penetraion = 0.f;

    if (ball.getVelocity().x < 0) {
        penetraion = paddleX2 - ballX1;
    } else if (ball.getVelocity().x > 0) {
        penetraion = paddleX1 - ballX2;
    }

    return {C::CollisionType::Paddle, penetraion};
}

std::pair<C::CollisionType, float> Game::checkWallCollision() {
    float ballX1 = ball.getPosition().x;
    float ballX2 = ball.getPosition().x + C::BALL_WIDTH;
    float ballY1 = ball.getPosition().y;
    float ballY2 = ball.getPosition().y + C::BALL_HEIGHT;

    std::pair<C::CollisionType, float> contact = {C::CollisionType::None, 0.f};

    if (ballX1 < 0.f) {
        contact.first = C::CollisionType::Left;

    } else if (ballX2 > C::WINDOW_WIDTH) {
        contact.first = C::CollisionType::Right;

    } else if (ballY2 < 0.f) {
        contact.first = C::CollisionType::Top;
        contact.second = -ballY1;

    } else if (ballY1 > C::WINDOW_HEIGHT) {
        contact.first = C::CollisionType::Bottom;
        contact.second = C::WINDOW_HEIGHT - ballY2;
    }

    return contact;
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