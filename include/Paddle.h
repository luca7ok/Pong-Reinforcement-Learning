#pragma once

#include <SFML/Graphics.hpp>

class Paddle : public sf::Drawable {
private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Paddle(sf::Vector2f position);

    ~Paddle() = default;

    void update(float dt);

    sf::Vector2f getPosition() const;

    void setVelocity(sf::Vector2f newVelocity);
};