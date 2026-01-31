#include "Paddle.h"

#include "Constants.h"

namespace C = Constants;

Paddle::Paddle(sf::Vector2f position) {
    shape.setSize(sf::Vector2f(C::PADDLE_WIDTH, C::PADDLE_HEIGHT));
    shape.setPosition(position);
}

void Paddle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shape, states);
}