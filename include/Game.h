#pragma once

#include <SFML/Graphics.hpp>

#include "Ball.h"
#include "Paddle.h"
#include "Score.h"

class Game {
private:
    sf::RenderWindow window;
    Ball ball;
    Paddle paddlePlayer1;
    Paddle paddlePlayer2;
    Score scorePlayer1;
    Score scorePlayer2;

    void handleInput();

    void render();

    std::pair<C::CollisionType, float> checkPaddleCollision(const Paddle& paddle);

    std::pair<C::CollisionType, float> checkWallCollision();

public:
    Game();

    ~Game() = default;

    void run();
};  // namespace C=Constantsclass Game