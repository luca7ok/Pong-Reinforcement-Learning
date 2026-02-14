#include "Paddle.h"

#include <SFML/System/Vector2.hpp>

#include "Constants.h"

namespace C = Constants;

Paddle::Paddle(sf::Vector2f _position, sf::Vector2f _velocity, sf::Vector2f _size)
    : velocity{_velocity} {
    shape.setSize(_size);
    shape.setPosition(_position);
}

void Paddle::update(float dt) {
    sf::Vector2f newPosition = getPosition();

    newPosition.y += velocity.y * dt;

    if (newPosition.y < 0) {
        newPosition.y = 0.f;
    } else if (newPosition.y + C::PADDLE_HEIGHT > C::WINDOW_HEIGHT) {
        newPosition.y = C::WINDOW_HEIGHT - C::PADDLE_HEIGHT;
    }

    shape.setPosition(newPosition);
}

void Paddle::setVelocity(sf::Vector2f newVelocity) {
    velocity = newVelocity;
}

sf::Vector2f Paddle::getPosition() const {
    return shape.getPosition();
}

void Paddle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shape, states);
}