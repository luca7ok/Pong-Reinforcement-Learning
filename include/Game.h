#pragma once
#include <SFML/Graphics.hpp>

#include "Constants.h"

class Game {
private:
    sf::RenderWindow window;

public:
    Game();
    ~Game() = default;

    void run();
};