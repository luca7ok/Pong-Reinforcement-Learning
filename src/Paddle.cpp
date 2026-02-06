#include "Paddle.h"

#include "Constants.h"

namespace C = Constants;

Paddle::Paddle(sf::Vector2f position) : velocity{sf::Vector2f(0, C::PADDLE_SPEED)} {
    shape.setSize(sf::Vector2f(C::PADDLE_WIDTH, C::PADDLE_HEIGHT));
    shape.setPosition(position);
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