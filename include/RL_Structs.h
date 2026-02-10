#pragma once

#include "SFML/Graphics.hpp"

namespace RL_Structs {
    struct GameState {
        float ballX;
        float ballY;
        sf::Vector2f ballVelocity;
        float paddleY;
        float enemyY;
    };

    struct Experience {
        GameState state;
        int action;
        float reward;
        GameState nextState;
        bool done;
    };
} // namespace RL_Structs
