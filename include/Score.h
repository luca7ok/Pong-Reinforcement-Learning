#pragma once

#include <SFML/Graphics.hpp>

class Score : public sf::Drawable {
private:
    sf::Font font;
    sf::Text text;
    bool rightAligned;
    int score;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void updateOrigin();

public:
    Score(sf::Vector2f position, bool rightAligned);

    void increment();

    ~Score() = default;
};