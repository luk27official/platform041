#pragma once
 
#include <SFML/Graphics.hpp>
 
class Coin {
private:
    sf::Sprite sprite;
    sf::Texture txt;

public:
    bool isCollected = false;
    
    Coin() {
        txt.loadFromFile("res/coin.png");
        sprite.setTexture(txt);
    }
 
    void drawTo(sf::RenderWindow &window) {
        window.draw(sprite);
    }
 
    sf::FloatRect getGlobalBounds() {
        return sprite.getGlobalBounds();
    }
 
    void setPos(sf::Vector2f newPos) {
        sprite.setPosition(newPos);
    }

};