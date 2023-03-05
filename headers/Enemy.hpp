#pragma once
 
#include "SFML/Graphics.hpp"
#include "Direction.hpp"

/**
 * @brief A class that represents an enemy. Meant to be drawn to the screen.
 */
class Enemy {
private:
    sf::Sprite sprite;
    sf::Texture txt;

public:
    Direction direction;
    bool isAlive = true;
    float gravity = 800;
    float moveSpeed = 150;

    /**
     * @brief Creates a new enemy with the given gravity, move speed and path to the texture. The enemy size is based on the texture size.
     */
    Enemy(float gravity, float moveSpeed, const std::string& texturePath);

    Enemy(const Enemy&) = delete;
    Enemy& operator=(const Enemy&) = delete;

    /*
    * @brief Draws the enemy to the window
    */
    void drawTo(sf::RenderWindow &window);

    /*
    * @brief Moves the enemy by the given distance
    */
    void move(const sf::Vector2f distance);
 
    /*
    * @brief Sets the position of the enemy
    */
    void setPos(const sf::Vector2f newPos);
 
    /*
    * @brief Returns the y position of the enemy
    */
    int getY();

    /*
    * @brief Returns the x position of the enemy
    */
    int getX();

    /*
    * @brief Returns the global bounds of the enemy (used for collision detection)    
    */
    sf::FloatRect getGlobalBounds();

    /*
    * @brief Checks for collision with the given rectangle on the left side. Returns true if there is a collision.
    */
    bool leftObstacleCollision(const sf::RectangleShape& rect);

    /*
    * @brief Checks for collision with the given rectangle on the right side. Returns true if there is a collision. To see more about the collision detection, see leftObstacleCollision().
    */
    bool rightObstacleCollision(const sf::RectangleShape& rect);
    
    /*
    * @brief Checks for collision with the given rectangle on the bottom side. Returns true if there is a collision. To see more about the collision detection, see leftObstacleCollision().
    */
    bool bottomObstacleCollision(const sf::RectangleShape& rect);

    /*
    * @brief Checks for collision with the given rectangle on the top side. Returns true if there is a collision. To see more about the collision detection, see leftObstacleCollision().
    */
    bool topObstacleCollision(const sf::RectangleShape& rect);
};