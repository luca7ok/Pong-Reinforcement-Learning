#pragma once

#include <SFML/Graphics.hpp>

class Paddle : public sf::Drawable {
private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Vector2f getPosition() const;

public:
    Paddle(sf::Vector2f position);

    ~Paddle() = default;

    void update(float dt);

    void setVelocity(sf::Vector2f newVelocity);
};