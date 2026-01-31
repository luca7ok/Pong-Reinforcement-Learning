#include "Ball.h"

#include "Constants.h"

namespace C = Constants;

Ball::Ball() {
    shape.setSize(sf::Vector2f(C::BALL_WIDTH, C::BALL_HEIGHT));
    shape.setPosition(sf::Vector2f(C::BALL_START_X, C::BALL_START_Y));
};

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shape, states);
}