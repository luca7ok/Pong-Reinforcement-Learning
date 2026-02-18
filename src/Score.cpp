#include "Score.h"

#include <SFML/System/Vector2.hpp>

Score::Score(sf::Vector2f position, bool _rightAligned)
    : score{0}, rightAligned{_rightAligned}, initialPosition(position) {
    if (!font.loadFromFile("assets/micro5.ttf")) {
        throw std::runtime_error("Failed to load");
    }
    text.setFont(font);
    text.setCharacterSize(120);
    text.setString(std::to_string(score));

    updateOrigin();
    text.setPosition(position);
}

void Score::increment() {
    score++;
    text.setString(std::to_string(score));
    updateOrigin();
}

void Score::reset() {
    score = 0;
    text.setString(std::to_string(score));

    updateOrigin();
    text.setPosition(initialPosition);
}

void Score::updateOrigin() {
    sf::FloatRect bounds = text.getLocalBounds();

    if (rightAligned) {
        text.setOrigin(bounds.left + bounds.width, bounds.top);
    } else {
        text.setOrigin(bounds.left, bounds.top);
    }
}

void Score::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(text);
}