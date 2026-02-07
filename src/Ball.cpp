#include "Ball.h"

#include <cmath>
#include <random>

#include "Constants.h"

namespace C = Constants;

Ball::Ball() : velocity{sf::Vector2f{C::INITIAL_BALL_SPEED, 0.f}} {
    shape.setSize(sf::Vector2f(C::BALL_WIDTH, C::BALL_HEIGHT));
    shape.setPosition(sf::Vector2f(C::BALL_X, C::BALL_Y));
};

void Ball::update(float dt) {
    sf::Vector2f newPostion = getPosition();

    newPostion += velocity * dt;

    shape.setPosition(newPostion);
}

void Ball::collideWithPaddle(const C::CollisionType& contactType, float penetration) {
    shape.setPosition(sf::Vector2f(shape.getPosition().x + penetration, shape.getPosition().y));

    float directionX = (velocity.x > 0) ? -1.f : 1.f;
    if (contactType == C::CollisionType::Top) {
        velocity.x = C::BALL_SPEED * directionX * 0.7f;
        velocity.y = -0.7f * C::BALL_SPEED;

    } else if (contactType == C::CollisionType::Middle) {
        std::random_device randomDevice;
        std::mt19937 gen(randomDevice());
        std::bernoulli_distribution d(0.5);
        int sign = d(gen) ? 1 : -1;

        velocity.x = C::BALL_SPEED * directionX;
        velocity.y = 0.f;

    } else if (contactType == C::CollisionType::Bottom) {
        velocity.x = C::BALL_SPEED * directionX * 0.7f;
        velocity.y = 0.7 * C::BALL_SPEED;
    }
}

void Ball::collideWithWall(const C::CollisionType& contactType, float penetration) {
    if (contactType == C::CollisionType::Top || contactType == C::CollisionType::Bottom) {
        shape.setPosition(sf::Vector2f(shape.getPosition().x, shape.getPosition().y + penetration));
        velocity.y = -velocity.y;

    } else if (contactType == C::CollisionType::Left) {
        shape.setPosition(sf::Vector2f(C::BALL_X, C::BALL_Y));
        velocity.x = C::INITIAL_BALL_SPEED;
        velocity.y = 0.75f * C::INITIAL_BALL_SPEED;

    } else if (contactType == C::CollisionType::Right) {
        shape.setPosition(sf::Vector2f(C::BALL_X, C::BALL_Y));
        velocity.x = -C::INITIAL_BALL_SPEED;
        velocity.y = 0.75f * C::INITIAL_BALL_SPEED;
    }
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