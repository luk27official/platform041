//
// Created by luk27 on 05.03.2023.
//
#include "../headers/Enemy.hpp"

Enemy::Enemy(float gravity, float moveSpeed, const std::string &texturePath) {
    direction = Direction::Left;

    this->gravity = gravity;
    this->moveSpeed = moveSpeed;

    txt.loadFromFile(texturePath);
    sprite.setTexture(txt);
}

void Enemy::drawTo(sf::RenderWindow &window) {
    window.draw(sprite);
}

void Enemy::move(const sf::Vector2f distance) {
    sprite.move(distance);
}

void Enemy::setPos(const sf::Vector2f newPos) {
    sprite.setPosition(newPos);
}

int Enemy::getY() {
    return sprite.getPosition().y;
}

int Enemy::getX() {
    return sprite.getPosition().x;
}

sf::FloatRect Enemy::getGlobalBounds() {
    return sprite.getGlobalBounds();
}

bool Enemy::leftObstacleCollision(const sf::RectangleShape &rect) {
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

bool Enemy::rightObstacleCollision(const sf::RectangleShape &rect) {
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

bool Enemy::bottomObstacleCollision(const sf::RectangleShape &rect) {
    if (sprite.getGlobalBounds().intersects(rect.getGlobalBounds())) {
        if (sprite.getPosition().y + sprite.getGlobalBounds().height - 1 < rect.getPosition().y) {
            return true;
        }
    }
    return false;
}

bool Enemy::topObstacleCollision(const sf::RectangleShape &rect) {
    if (sprite.getGlobalBounds().intersects(rect.getGlobalBounds())) {
        if (sprite.getPosition().y + 1 > rect.getPosition().y + rect.getGlobalBounds().height) {
            return true;
        }
    }
    return false;
}
