#pragma once
 
#include <SFML/Graphics.hpp>
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
    Enemy(float gravity, float moveSpeed, const std::string& texturePath)
    {
        direction = Direction::Left;

        this->gravity = gravity;
        this->moveSpeed = moveSpeed;

        txt.loadFromFile(texturePath);
        sprite.setTexture(txt);
    }

    Enemy(const Enemy&) = delete;
    Enemy& operator=(const Enemy&) = delete;

    /*
    * @brief Draws the enemy to the window
    */
    void drawTo(sf::RenderWindow &window) {
        window.draw(sprite);
    }

    /*
    * @brief Moves the enemy by the given distance
    */
    void move(const sf::Vector2f distance) {
        sprite.move(distance);
    }
 
    /*
    * @brief Sets the position of the enemy
    */
    void setPos(const sf::Vector2f newPos) {
        sprite.setPosition(newPos);
    }
 
    /*
    * @brief Returns the y position of the enemy
    */
    int getY() {
        return sprite.getPosition().y;
    }

    /*
    * @brief Returns the x position of the enemy
    */
    int getX() {
        return sprite.getPosition().x;
    }

    /*
    * @brief Returns the global bounds of the enemy (used for collision detection)    
    */
    sf::FloatRect getGlobalBounds() {
        return sprite.getGlobalBounds();
    }

    /*
    * @brief Checks for collision with the given rectangle on the left side. Returns true if there is a collision.
    */
    bool leftObstacleCollision(const sf::RectangleShape& rect) {
        //if the enemy is colliding with the bottom or top of the rectangle, it is not colliding with the left side 
        if(bottomObstacleCollision(rect) || topObstacleCollision(rect)) {
            return false;
        }

        //check the collision by comparing the bounds of the enemy and the rectangle, watch out that this only works if the enemy is slow enough
        if (sprite.getGlobalBounds().intersects(rect.getGlobalBounds())) {
            if (sprite.getPosition().x + sprite.getGlobalBounds().width - 1 > rect.getPosition().x) {
                return true;
            }
        }
        return false;
    }

    /*
    * @brief Checks for collision with the given rectangle on the right side. Returns true if there is a collision. To see more about the collision detection, see leftObstacleCollision().
    */
    bool rightObstacleCollision(const sf::RectangleShape& rect) {
        if(bottomObstacleCollision(rect) || topObstacleCollision(rect)) {
            return false;
        }

        if (sprite.getGlobalBounds().intersects(rect.getGlobalBounds())) {
            if (sprite.getPosition().x + 1 < rect.getPosition().x + rect.getGlobalBounds().width) {
                return true;
            }
        }
        return false;
    }
    
    /*
    * @brief Checks for collision with the given rectangle on the bottom side. Returns true if there is a collision. To see more about the collision detection, see leftObstacleCollision().
    */
    bool bottomObstacleCollision(const sf::RectangleShape& rect) {
        if (sprite.getGlobalBounds().intersects(rect.getGlobalBounds())) {
            if (sprite.getPosition().y + sprite.getGlobalBounds().height - 1 < rect.getPosition().y) {
                return true;
            }
        }
        return false;
    }

    /*
    * @brief Checks for collision with the given rectangle on the top side. Returns true if there is a collision. To see more about the collision detection, see leftObstacleCollision().
    */
    bool topObstacleCollision(const sf::RectangleShape& rect) {
        if (sprite.getGlobalBounds().intersects(rect.getGlobalBounds())) {
            if (sprite.getPosition().y + 1 > rect.getPosition().y + rect.getGlobalBounds().height) {
                return true;
            }
        }
        return false;
    }
};