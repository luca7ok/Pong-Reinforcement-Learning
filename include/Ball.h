#pragma once

#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Paddle.h"

namespace C = Constants;

class Ball : public sf::Drawable {
private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void reset();

public:
    Ball();

    ~Ball() = default;

    void update(float dt);

    void collideWithPaddle(const Paddle& paddle, float penetration);

    void collideWithWall(const C::CollisionType& contactType, float penetration);

    sf::Vector2f getPosition() const;

    sf::Vector2f getVelocity() const;

    void setVelocity(sf::Vector2f newVelocity);
};