#pragma once
 
#include <SFML/Graphics.hpp>
 
enum class EnemyType {
    EnemyOne
};

class Enemy {
private:
    sf::Sprite sprite;
    sf::Texture txt;

    EnemyType type;

public:
    Enemy() {
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
};