#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Score : public sf::Drawable {
private:
    sf::Font font;
    sf::Text text;
    bool rightAligned;
    int score;
    sf::Vector2f initialPosition;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void updateOrigin();

public:
    Score(sf::Vector2f position, bool rightAligned);

    ~Score() = default;

    void increment();

    void reset();
};