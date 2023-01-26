#pragma once
 
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Coin.hpp"
 
class Player {
private:
    sf::Sprite sprite;
    sf::Texture texture;

public:

    Player() {
        sprite.setPosition({ 0, 500 });
        texture.loadFromFile("res/player.png");
        sprite.setTexture(texture);
    }
 
    void drawTo(sf::RenderWindow &window) {
        window.draw(sprite);
    }

    void move(sf::Vector2f distance) {
        sprite.move(distance);
    }
 
    void setPos(sf::Vector2f newPos) {
        sprite.setPosition(newPos);
    }
 
    int getY() {
        return sprite.getPosition().y;
    }

    int getX() {
        return sprite.getPosition().x;
    }
 
    bool isCollidingWithCoin(Coin& coin) {
        if (sprite.getGlobalBounds().intersects(coin.getGlobalBounds())) {
            return true;
        }
        return false;
    }

    bool leftObstacleCollision(sf::RectangleShape& rect) {
        if(bottomObstacleCollision(rect) || topObstacleCollision(rect)) {
            return false;
        }

        if (sprite.getGlobalBounds().intersects(rect.getGlobalBounds())) {
            if (sprite.getPosition().x + sprite.getGlobalBounds().width - 1 > rect.getPosition().x) {
                //std::cout << "a: " << sprite.getPosition().x + sprite.getGlobalBounds().width << " b: " << rect.getPosition().x - 1 << std::endl;
                return true;
            }
        }
        return false;
    }

    bool rightObstacleCollision(sf::RectangleShape& rect) {
        if(bottomObstacleCollision(rect) || topObstacleCollision(rect)) {
            return false;
        }

        if (sprite.getGlobalBounds().intersects(rect.getGlobalBounds())) {
            if (sprite.getPosition().x + 1 < rect.getPosition().x + rect.getGlobalBounds().width) {
                //std::cout << "a: " << sprite.getPosition().x + 1 << " b: " << rect.getPosition().x + rect.getGlobalBounds().width << std::endl;
                return true;
            }
        }
        return false;
    }
    
    bool bottomObstacleCollision(sf::RectangleShape& rect) {
        if (sprite.getGlobalBounds().intersects(rect.getGlobalBounds())) {
            if (sprite.getPosition().y + sprite.getGlobalBounds().height - 1 < rect.getPosition().y) {
                //std::cout << "ax: " << sprite.getPosition().y + sprite.getGlobalBounds().height << " b: " << rect.getPosition().y << std::endl;
                return true;
            }
        }
        return false;
    }

    bool topObstacleCollision(sf::RectangleShape& rect) {
        if (sprite.getGlobalBounds().intersects(rect.getGlobalBounds())) {
            if (sprite.getPosition().y + 1 > rect.getPosition().y + rect.getGlobalBounds().height) {
                return true;
            }
        }
        return false;
    }
};