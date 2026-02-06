#include "Ball.h"

#include "Constants.h"

namespace C = Constants;

Ball::Ball() : velocity{sf::Vector2f{C::BALL_SPEED, 0.f}} {
    shape.setSize(sf::Vector2f(C::BALL_WIDTH, C::BALL_HEIGHT));
    shape.setPosition(sf::Vector2f(C::BALL_X, C::BALL_Y));
};

void Ball::update(float dt) {
    sf::Vector2f newPostion = getPosition();

    newPostion += velocity * dt;

    shape.setPosition(newPostion);
}

sf::Vector2f Ball::getPosition() const {
    return shape.getPosition();
}

sf::Vector2f Ball::getVelocity() const {
    return velocity;
}

void Ball::setVelocity(sf::Vector2f newVelocity) {
    velocity = newVelocity;
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shape, states);
}