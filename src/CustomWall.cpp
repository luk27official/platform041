#include "../headers/CustomWall.hpp"

void CustomWall::drawTo(sf::RenderWindow &window) {
    window.draw(shape);
}

sf::FloatRect CustomWall::getGlobalBounds() {
    return shape.getGlobalBounds();
}

void CustomWall::setPos(const sf::Vector2f newPos) {
    shape.setPosition(newPos);
}

void CustomWall::setSize(const sf::Vector2f size) {
    shape.setSize(size);
}

sf::RectangleShape CustomWall::getShape() {
    return shape;
}

void CustomWall::setFillColor(const sf::Color color) {
    shape.setFillColor(color);
}
