#pragma once

#include <SFML/Graphics.hpp>
#include "Direction.hpp"
#include "Enemy.hpp"

#include <memory>

/**
 * @brief A class that represents a bullet. Meant to be drawn to the screen.
*/
class Bullet {
private:
    sf::CircleShape shape;
    //sf::Texture txt;

public:
    Direction direction;
    const int bulletSpeed = 500;

    Bullet() {
        //currently not using a texture
        //txt.loadFromFile("res/bullet.png");
        //shape.setTexture(&txt);
        shape.setRadius(5);
        shape.setFillColor(sf::Color::Blue);
    }

    /*
    * @brief Draws the bullet to the window
    */
    void drawTo(sf::RenderWindow &window) {
        window.draw(shape);
    }

    /*
    * @brief Returns the global bounds of the bullet (used for collision detection)    
    */
    sf::FloatRect getGlobalBounds() {
        return shape.getGlobalBounds();
    }

    /*
    * @brief Sets the position of the bullet
    */
    void setPos(sf::Vector2f newPos) {
        shape.setPosition(newPos);
    }

    /*
    * @brief Moves the bullet by the given distance
    */
    void move(sf::Vector2f distance) {
        shape.move(distance);
    }

    /*
    * @brief Returns the y position of the bullet
    */
    int getY() {
        return shape.getPosition().y;
    }

    /*
    * @brief Returns the x position of the bullet
    */
    int getX() {
        return shape.getPosition().x;
    }

    /*
    * @brief Returns true, if the bullet is colliding with the given enemy
    */
    bool isCollidingWithEnemy(std::shared_ptr<Enemy> enemy) {
        if (shape.getGlobalBounds().intersects(enemy->getGlobalBounds())) {
            return true;
        }
        return false;
    }

    /*
    * @brief Returns true, if the bullet is colliding with the given obstacle
    */
    bool isCollidingWithObstacle(sf::RectangleShape& rect) {
        if (shape.getGlobalBounds().intersects(rect.getGlobalBounds())) {
            return true;
        }
        return false;
    }
};