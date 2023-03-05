#pragma once

#include "SFML/Graphics.hpp"
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

    Bullet();

    Bullet(const Bullet&) = delete;
    Bullet& operator=(const Bullet&) = delete;
    
    /*
    * @brief Draws the bullet to the window
    */
    void drawTo(sf::RenderWindow &window);

    /*
    * @brief Returns the global bounds of the bullet (used for collision detection)    
    */
    sf::FloatRect getGlobalBounds();

    /*
    * @brief Sets the position of the bullet
    */
    void setPos(const sf::Vector2f newPos);

    /*
    * @brief Moves the bullet by the given distance
    */
    void move(const sf::Vector2f distance);

    /*
    * @brief Returns the y position of the bullet
    */
    int getY();

    /*
    * @brief Returns the x position of the bullet
    */
    int getX();

    /*
    * @brief Returns true, if the bullet is colliding with the given enemy
    */
    bool isCollidingWithEnemy(Enemy* enemy);

    /*
    * @brief Returns true, if the bullet is colliding with the given obstacle
    */
    bool isCollidingWithObstacle(const sf::RectangleShape& rect);
};
