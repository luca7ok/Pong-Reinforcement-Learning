#pragma once

#include <SFML/Graphics.hpp>

class Paddle : public sf::Drawable, public sf::Transformable {
private:
    sf::RectangleShape shape;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Paddle(sf::Vector2f position);

    ~Paddle() = default;
};