#pragma once

#include <SFML/Graphics.hpp>

class Ball : public sf::Drawable, public sf::Transformable {
private:
    sf::RectangleShape shape;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Ball();

    ~Ball() = default;
};