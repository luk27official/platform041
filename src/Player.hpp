#pragma once
 
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Coin.hpp"
#include "Enemy.hpp"
#include "Constants.hpp"

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

    Player() {
        direction = Direction::Right;
        sprite.setPosition({ 0, 500 });
        texture_left.loadFromFile("res/player_left.png");
        texture_right.loadFromFile("res/player.png");
        sprite.setTexture(texture_right);
    }
 
    /*
    * @brief Draws the player to the window
    */
    void drawTo(sf::RenderWindow &window) {
        window.draw(sprite);
    }

    /*
    * @brief Moves the player by the given distance
    */
    void move(const sf::Vector2f distance) {
        sprite.move(distance);
    }
 
    /*
    * @brief Sets the position of the player
    */
    void setPos(const sf::Vector2f newPos) {
        sprite.setPosition(newPos);
    }

    /*
    * @brief Flips the sprite to the correct direction
    */
    void flipSprite() {
        //note: here we could just use the scale method, but that moves the sprite as well which we don't want
        if (direction == Direction::Left) {
            sprite.setTexture(texture_left);
        }
        else {
            sprite.setTexture(texture_right);
        }
    }

    /*
    * @brief Returns the width of the player
    */
    int getWidth() {
        return sprite.getGlobalBounds().width;
    }

    /*
    * @brief Returns the height of the player
    */
    int getHeight() {
        return sprite.getGlobalBounds().height;
    }
 
    /*
    * @brief Returns the y position of the player
    */
    int getY() {
        return sprite.getPosition().y;
    }

    /*
    * @brief Returns the x position of the player
    */
    int getX() {
        return sprite.getPosition().x;
    }

    /*
    * @brief Method that is called when the player dies, resets the player position and resets the view
    */
    void die(sf::RenderWindow &window) {
        window.setView(sf::View(sf::Vector2f(0, Constants::get_window_height() / 2.0), sf::Vector2f(Constants::get_window_width(), Constants::get_window_height())));
        sprite.setPosition({ 0, 500 });
    }
 
    /*
    * @brief Returns true if the player is colliding with the given coin
    */
    bool isCollidingWithCoin(Coin* coin) {
        if (sprite.getGlobalBounds().intersects(coin->getGlobalBounds())) {
            return true;
        }
        return false;
    }

    /*
    * @brief Returns true if the player is colliding with the given obstacle on the left side. For more reference see Enemy.leftObstacleCollision()
    */
    bool leftObstacleCollision(const sf::RectangleShape& rect) {
        if(bottomObstacleCollision(rect) || topObstacleCollision(rect)) {
            return false;
        }

        if (sprite.getGlobalBounds().intersects(rect.getGlobalBounds())) {
            if (sprite.getPosition().x + sprite.getGlobalBounds().width - 1 > rect.getPosition().x) {
                return true;
            }
        }
        return false;
    }

    /*
    * @brief Returns true if the player is colliding with the given obstacle on the right side. For more reference see Enemy.leftObstacleCollision()
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
    * @brief Returns true if the player is colliding with the given obstacle on the bottom side. For more reference see Enemy.leftObstacleCollision()
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
    * @brief Returns true if the player is colliding with the given obstacle on the top side. For more reference see Enemy.leftObstacleCollision()
    */
    bool topObstacleCollision(const sf::RectangleShape& rect) {
        if (sprite.getGlobalBounds().intersects(rect.getGlobalBounds())) {
            if (sprite.getPosition().y + 1 > rect.getPosition().y + rect.getGlobalBounds().height) {
                return true;
            }
        }
        return false;
    }

    /*
    * @brief Returns true if the player is colliding with the given enemy
    */
    bool isCollidingWithEnemy(Enemy* enemy) {
        if (sprite.getGlobalBounds().intersects(enemy->getGlobalBounds())) {
            return true;
        }
        return false;
    }
};