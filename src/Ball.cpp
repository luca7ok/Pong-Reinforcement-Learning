#include "Ball.h"

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

void Ball::collideWithPaddle(const Paddle& paddle, float penetration) {
    shape.setPosition(sf::Vector2f(shape.getPosition().x + penetration, shape.getPosition().y));

    float paddleCenterY = paddle.getPosition().y + (C::PADDLE_HEIGHT / 2.f);
    float ballCenterY = shape.getPosition().y + (C::BALL_HEIGHT / 2.f);

    float relativeIntersectY =
        std::clamp((ballCenterY - paddleCenterY) / (C::PADDLE_HEIGHT / 2.f), -1.f, 1.f);

    float bounceAngle = relativeIntersectY * C::MAX_BOUNCE_ANGLE;
    float directionX = (velocity.x > 0) ? -1.f : 1.f;
    float newVelocityX = C::BALL_SPEED * std::cos(bounceAngle);
    float newVelocityY = C::BALL_SPEED * std::sin(bounceAngle);

    float minXSpeed = C::BALL_SPEED * 0.5f;
    if (std::abs(newVelocityX) < minXSpeed) {
        newVelocityX = (newVelocityX > 0) ? minXSpeed : -minXSpeed;
    }

    velocity.x = newVelocityX * directionX;
    velocity.y = newVelocityY;
}

void Ball::collideWithWall(const C::CollisionType& contactType, float penetration) {
    if (contactType == C::CollisionType::Top || contactType == C::CollisionType::Bottom) {
        shape.setPosition(sf::Vector2f(shape.getPosition().x, shape.getPosition().y + penetration));
        velocity.y = -velocity.y;

    } else if (contactType == C::CollisionType::Left) {
        reset();

    } else if (contactType == C::CollisionType::Right) {
        reset();
    }
}

void Ball::reset() {
    shape.setPosition(sf::Vector2f(C::BALL_X, C::BALL_Y));

    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
    std::bernoulli_distribution distribution(0.5);
    float directionX = distribution(gen) ? 1.f : -1.f;

    std::uniform_real_distribution<float> disttributionAngle(-C::MAX_LAUNCH_ANGLE,
                                                             C::MAX_LAUNCH_ANGLE);

    float angle = disttributionAngle(gen);

    velocity.x = C::INITIAL_BALL_SPEED * std::cos(angle) * directionX;
    velocity.y = C::INITIAL_BALL_SPEED * std::sin(angle);
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