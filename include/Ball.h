#pragma once

#include <SFML/Graphics.hpp>

class Ball : public sf::Drawable {
private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Ball();

    ~Ball() = default;

    void update(float dt);

    sf::Vector2f getPosition() const;

    sf::Vector2f getVelocity() const;

    void setVelocity(sf::Vector2f newVelocity);
};