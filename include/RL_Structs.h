#pragma once

#include <array>

#include "SFML/Graphics.hpp"

namespace RL_Structs {
    struct GameState {
        float ballX;
        float ballY;
        sf::Vector2f ballVelocity;
        float paddleY;
        float enemyY;
    };

    using StackedState = std::array<GameState, 4>;

    struct Experience {
        StackedState state;
        int action;
        float reward;
        StackedState nextState;
        bool done;
    };
}  // namespace RL_Structs
