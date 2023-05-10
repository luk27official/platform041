#include "../headers/GoldenWallAdapter.hpp"

GoldenWallAdapter::GoldenWallAdapter() {
    type = WallType::GoldenWall;
}

void GoldenWallAdapter::drawTo(sf::RenderWindow &window) {
    window.draw(this->rectangle);
}

sf::FloatRect GoldenWallAdapter::getGlobalBounds() {
    return this->rectangle.getGlobalBounds();
}

void GoldenWallAdapter::setPos(const sf::Vector2f newPos) {
    //do not allow the golden wall to have a negative x or y position
    if(newPos.x < 0 || newPos.y < 0) {
        return;
    }

    //we have to update the x and y values of the wall as well
    //so we directly call the GoldenWall inherited methods
    this->setX(newPos.x);
    this->setY(newPos.y);

    this->rectangle.setPosition(newPos);
}

void GoldenWallAdapter::setSize(const sf::Vector2f size) {
    this->rectangle.setSize(size);
}

sf::RectangleShape GoldenWallAdapter::getShape() {
    return rectangle;
}

void GoldenWallAdapter::setFillColor(const sf::Color color) {
    this->rectangle.setFillColor(color);
}
