#pragma once

#include <SFML/Graphics.hpp>

#include "Ball.h"
#include "Paddle.h"
#include "RL_Structs.h"
#include "Score.h"

namespace RL = RL_Structs;

class Game {
private:
    sf::RenderWindow window;
    Ball ball;
    Paddle leftPaddle;
    Paddle rightPaddle;
    Score leftScore;
    Score rightScore;
    bool shouldRender;

    void handleInput();

    void render();

    std::pair<C::CollisionType, float> checkPaddleCollision(const Paddle& paddle);

    std::pair<C::CollisionType, float> checkWallCollision();

    void updateHardCodedAI();

public:
    Game();

    ~Game() = default;

    void run();

    void reset();

    std::tuple<RL::GameState, float, bool> step(int action);

    RL::GameState getGameState() const;

    void setShouldRender(bool renderMode);
};