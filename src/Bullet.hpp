#pragma once

#include <SFML/Graphics.hpp>
#include "Direction.hpp"

class Bullet {
private:
    sf::CircleShape shape;
    //sf::Texture txt;

public:
    Direction direction;
    const int bulletSpeed = 500;

    Bullet() {
        //txt.loadFromFile("res/bullet.png");
        //shape.setTexture(&txt);
        shape.setRadius(5);
        shape.setFillColor(sf::Color::Blue);
    }

    void drawTo(sf::RenderWindow &window) {
        window.draw(shape);
    }

    sf::FloatRect getGlobalBounds() {
        return shape.getGlobalBounds();
    }

    void setPos(sf::Vector2f newPos) {
        shape.setPosition(newPos);
    }

    void move(sf::Vector2f distance) {
        shape.move(distance);
    }

    int getY() {
        return shape.getPosition().y;
    }

    int getX() {
        return shape.getPosition().x;
    }

    bool isCollidingWithEnemy(std::shared_ptr<Enemy> enemy) {
        if (shape.getGlobalBounds().intersects(enemy->getGlobalBounds())) {
            return true;
        }
        return false;
    }

    bool isCollidingWithObstacle(sf::RectangleShape& rect) {
        if (shape.getGlobalBounds().intersects(rect.getGlobalBounds())) {
            return true;
        }
        return false;
    }
};