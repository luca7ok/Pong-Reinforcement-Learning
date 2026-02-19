#pragma once

#define _USE_MATH_DEFINES

#include <cmath>
#include <string>

namespace Constants {
    inline constexpr int WINDOW_WIDTH{1280};
    inline constexpr int WINDOW_HEIGHT{720};
    inline constexpr const char* WINDOW_NAME{"Pong"};

    inline constexpr int FRAMERATE_LIMIT{60};

    inline constexpr int LINE_LENGTH{20};
    inline constexpr int NO_LINES{WINDOW_HEIGHT / LINE_LENGTH + 1};

    inline constexpr float BALL_WIDTH{15.f};
    inline constexpr float BALL_HEIGHT{15.f};
    inline constexpr float BALL_X{WINDOW_WIDTH / 2.f - BALL_WIDTH / 2.f};
    inline constexpr float BALL_Y{WINDOW_HEIGHT / 2.f - BALL_WIDTH / 2.f};

    inline constexpr float PADDLE_WIDTH{20.f};
    inline constexpr float PADDLE_HEIGHT{100.f};
    inline constexpr float PADDLE_WALL_DISTANCE{50.f};
    inline constexpr float PADDLE_P1_X{PADDLE_WALL_DISTANCE};
    inline constexpr float PADDLE_P1_Y{WINDOW_HEIGHT / 2.f - PADDLE_HEIGHT / 2.f};
    inline constexpr float PADDLE_P2_X{WINDOW_WIDTH - PADDLE_WALL_DISTANCE};
    inline constexpr float PADDLE_P2_Y{WINDOW_HEIGHT / 2.f - PADDLE_HEIGHT / 2.f};

    inline constexpr float SCORE_NET_DISTANCE{50};
    inline constexpr float SCORE_P1_X{WINDOW_WIDTH / 2.f - SCORE_NET_DISTANCE};
    inline constexpr float SCORE_P1_Y{50.f};
    inline constexpr float SCORE_P2_X{WINDOW_WIDTH / 2.f + SCORE_NET_DISTANCE};
    inline constexpr float SCORE_P2_Y{50.f};

    inline constexpr float DEAD_ZONE{10.f};
    inline constexpr float PADDLE_SPEED{600.f};
    inline constexpr float AI_PADDLE_SPEED{PADDLE_SPEED * 0.9f};
    inline constexpr float INITIAL_BALL_SPEED{500.f};
    inline constexpr float MAX_BALL_SPEED{1200.f};
    inline constexpr float INITIAL_SPEED_MULTIPLIER{1.1f};

    inline constexpr float MAX_BOUNCE_ANGLE{60.f * (M_PI / 180.f)};
    inline constexpr float MAX_LAUNCH_ANGLE{25.f * (M_PI / 180.f)};

    inline constexpr int MAX_BUFFER_CAPACITY{10000};
    inline constexpr int BATCH_SIZE{64};
    inline constexpr float LEARNING_RATE{1e-3};
    inline constexpr float GAMMA{0.99f};
    inline constexpr float EPSILON{1.f};
    inline constexpr float EPSILON_DECAY{0.9995f};
    inline constexpr float EPSILON_MIN{0.01f};
    inline constexpr int TARGET_UPDATE_FREQ{1000};
    inline constexpr int INPUT_LAYER_SIZE{6};
    inline constexpr int HIDDEN_LAYER_SIZE{128};
    inline constexpr int OUTPUT_LAYER_SIZE{3};

    inline constexpr int EPISODES{1000};

    enum class CollisionType { None, Top, Paddle, Bottom, Left, Right };
}  // namespace Constants