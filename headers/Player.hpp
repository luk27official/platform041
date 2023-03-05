#pragma once
 
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Coin.hpp"
#include "Enemy.hpp"
#include "Constants.hpp"

#include <cmath>
#include <memory>

/**
 * @brief A class that represents the player. Meant to be drawn to the screen.
 */
class Player {
private:
    sf::Sprite sprite;
    sf::Texture texture_right;
    sf::Texture texture_left;

public:
    const float gravity = 800;
    const float moveSpeed = 300;
    const float resetJumpTime = 0.75; //time in seconds
    const float resetShootTime = 0.75; //time in seconds
    
    Direction direction;
    bool isJumping = false;
    bool isShooting = false;
    bool isMovingLeft = false;
    bool isMovingRight = false;

    Player();
 
    /*
    * @brief Draws the player to the window
    */
    void drawTo(sf::RenderWindow &window);

    /*
    * @brief Moves the player by the given distance
    */
    void move(const sf::Vector2f distance);
 
    /*
    * @brief Sets the position of the player
    */
    void setPos(const sf::Vector2f newPos);

    /*
    * @brief Flips the sprite to the correct direction
    */
    void flipSprite();

    /*
    * @brief Returns the width of the player
    */
    int getWidth();

    /*
    * @brief Returns the height of the player
    */
    int getHeight();
 
    /*
    * @brief Returns the y position of the player
    */
    int getY();

    /*
    * @brief Returns the x position of the player
    */
    int getX();

    /*
    * @brief Method that is called when the player dies, resets the player position and resets the view
    */
    void die(sf::RenderWindow &window);
 
    /*
    * @brief Returns true if the player is colliding with the given coin
    */
    bool isCollidingWithCoin(Coin* coin);

    /*
    * @brief Returns true if the player is colliding with the given obstacle on the left side. For more reference see Enemy.leftObstacleCollision()
    */
    bool leftObstacleCollision(const sf::RectangleShape& rect);

    /*
    * @brief Returns true if the player is colliding with the given obstacle on the right side. For more reference see Enemy.leftObstacleCollision()
    */
    bool rightObstacleCollision(const sf::RectangleShape& rect);
    
    /*
    * @brief Returns true if the player is colliding with the given obstacle on the bottom side. For more reference see Enemy.leftObstacleCollision()
    */
    bool bottomObstacleCollision(const sf::RectangleShape& rect);

    /*
    * @brief Returns true if the player is colliding with the given obstacle on the top side. For more reference see Enemy.leftObstacleCollision()
    */
    bool topObstacleCollision(const sf::RectangleShape& rect);

    /*
    * @brief Returns true if the player is colliding with the given enemy
    */
    bool isCollidingWithEnemy(Enemy* enemy);
};