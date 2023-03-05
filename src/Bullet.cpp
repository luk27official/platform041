#include "../headers/Bullet.hpp"

Bullet::Bullet() {
    //currently not using a texture
    //txt.loadFromFile("res/bullet.png");
    //shape.setTexture(&txt);
    shape.setRadius(5);
    shape.setFillColor(sf::Color::Blue);
}

int Bullet::getX() {
    return shape.getPosition().x;
}

int Bullet::getY() {
    return shape.getPosition().y;
}

void Bullet::move(const sf::Vector2f distance) {
    shape.move(distance);
}

void Bullet::drawTo(sf::RenderWindow &window) {
    window.draw(shape);
}

sf::FloatRect Bullet::getGlobalBounds() {
    return shape.getGlobalBounds();
}

void Bullet::setPos(const sf::Vector2f newPos) {
    shape.setPosition(newPos);
}

bool Bullet::isCollidingWithEnemy(Enemy *enemy) {
    if (shape.getGlobalBounds().intersects(enemy->getGlobalBounds())) {
        return true;
    }
    return false;
}

bool Bullet::isCollidingWithObstacle(const sf::RectangleShape &rect) {
    if (shape.getGlobalBounds().intersects(rect.getGlobalBounds())) {
        return true;
    }
    return false;
}