#pragma once
 
#include <SFML/Graphics.hpp>
 
enum class EnemyType {
    EnemyOne
};

enum class Direction {
    Left,
    Right
};

class Enemy {
private:
    sf::Sprite sprite;
    sf::Texture txt;

public:
    Direction direction;
    EnemyType type;

    const float gravity = 800;
    const float moveSpeed = 150;

    Enemy() {
        type = EnemyType::EnemyOne;
        direction = Direction::Left;

        sprite.setPosition({ 0, 500 });
        txt.loadFromFile("res/enemy.png");
        sprite.setTexture(txt);
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

    sf::FloatRect getGlobalBounds() {
        return sprite.getGlobalBounds();
    }

    bool leftObstacleCollision(sf::RectangleShape& rect) {
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

    bool rightObstacleCollision(sf::RectangleShape& rect) {
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
    
    bool bottomObstacleCollision(sf::RectangleShape& rect) {
        if (sprite.getGlobalBounds().intersects(rect.getGlobalBounds())) {
            if (sprite.getPosition().y + sprite.getGlobalBounds().height - 1 < rect.getPosition().y) {
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