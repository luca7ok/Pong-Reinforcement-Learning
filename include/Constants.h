#pragma once

#include <string>

namespace Constants {
    inline constexpr int WINDOW_WIDTH{1300};
    inline constexpr int WINDOW_HEIGHT{820};
    inline constexpr const char* WINDOW_NAME{"Pong"};

    inline constexpr int FRAMERATE_LIMIT{60};

    inline constexpr int LINE_LENGTH{20};
    inline constexpr int NO_LINES{WINDOW_HEIGHT / LINE_LENGTH + 1};

    inline constexpr float BALL_WIDTH{20};
    inline constexpr float BALL_HEIGHT{20};
    inline constexpr float BALL_X{WINDOW_WIDTH / 2.0f - BALL_WIDTH / 2.0f};
    inline constexpr float BALL_Y{WINDOW_HEIGHT / 2.0f - BALL_WIDTH / 2.0f};

    inline constexpr float PADDLE_WIDTH{15};
    inline constexpr float PADDLE_HEIGHT{WINDOW_HEIGHT / 6.0f};
    inline constexpr float PADDLE_WALL_DISTANCE{50};
    inline constexpr float PADDLE_P1_X{PADDLE_WALL_DISTANCE};
    inline constexpr float PADDLE_P1_Y{WINDOW_HEIGHT / 2.0f - PADDLE_HEIGHT / 2.0f};
    inline constexpr float PADDLE_P2_X{WINDOW_WIDTH - PADDLE_WALL_DISTANCE};
    inline constexpr float PADDLE_P2_Y{WINDOW_HEIGHT / 2.0f - PADDLE_HEIGHT / 2.0f};

    inline constexpr float SCORE_NET_DISTANCE{50};
    inline constexpr float SCORE_P1_X{WINDOW_WIDTH / 2.0f - SCORE_NET_DISTANCE};
    inline constexpr float SCORE_P1_Y{50};
    inline constexpr float SCORE_P2_X{WINDOW_WIDTH / 2.0f + SCORE_NET_DISTANCE};
    inline constexpr float SCORE_P2_Y{50};
}  // namespace Constants