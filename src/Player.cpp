//
// Created by luk27 on 05.03.2023.
//
#include "../headers/Player.hpp"

Player::Player() {
    direction = Direction::Right;
    sprite.setPosition({ 0, 500 });
    texture_left.loadFromFile("res/player_left.png");
    texture_right.loadFromFile("res/player.png");
    sprite.setTexture(texture_right);
}

void Player::drawTo(sf::RenderWindow &window) {
    window.draw(sprite);
}

void Player::move(const sf::Vector2f distance) {
    sprite.move(distance);
}

void Player::setPos(const sf::Vector2f newPos) {
    sprite.setPosition(newPos);
}

void Player::flipSprite() {
    //note: here we could just use the scale method, but that moves the sprite as well which we don't want
    if (direction == Direction::Left) {
        sprite.setTexture(texture_left);
    }
    else {
        sprite.setTexture(texture_right);
    }
}

int Player::getWidth() {
    return sprite.getGlobalBounds().width;
}

int Player::getHeight() {
    return sprite.getGlobalBounds().height;
}

int Player::getY() {
    return sprite.getPosition().y;
}

int Player::getX() {
    return sprite.getPosition().x;
}

void Player::die(sf::RenderWindow &window) {
    window.setView(sf::View(sf::Vector2f(0, Constants::get_window_height() / 2.0), sf::Vector2f(Constants::get_window_width(), Constants::get_window_height())));
    sprite.setPosition({ 0, 500 });
}

bool Player::isCollidingWithCoin(Coin *coin) {
    if (sprite.getGlobalBounds().intersects(coin->getGlobalBounds())) {
        return true;
    }
    return false;
}

bool Player::leftObstacleCollision(const sf::RectangleShape &rect) {
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

bool Player::rightObstacleCollision(const sf::RectangleShape &rect) {
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

bool Player::bottomObstacleCollision(const sf::RectangleShape &rect) {
    if (sprite.getGlobalBounds().intersects(rect.getGlobalBounds())) {
        if (sprite.getPosition().y + sprite.getGlobalBounds().height - 1 < rect.getPosition().y) {
            return true;
        }
    }
    return false;
}

bool Player::topObstacleCollision(const sf::RectangleShape &rect) {
    if (sprite.getGlobalBounds().intersects(rect.getGlobalBounds())) {
        if (sprite.getPosition().y + 1 > rect.getPosition().y + rect.getGlobalBounds().height) {
            return true;
        }
    }
    return false;
}

bool Player::isCollidingWithEnemy(Enemy *enemy) {
    if (sprite.getGlobalBounds().intersects(enemy->getGlobalBounds())) {
        return true;
    }
    return false;
}
