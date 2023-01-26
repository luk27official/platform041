#pragma once
 
#include <SFML/Graphics.hpp>
 
class Coin {
public:
    Coin() {
        coin.setRadius(20);
        coin.setFillColor(sf::Color::Yellow);
    }
 
    void drawTo(sf::RenderWindow &window) {
        window.draw(coin);
    }
 
    sf::FloatRect getGlobalBounds() {
        return coin.getGlobalBounds();
    }
 
    void setPos(sf::Vector2f newPos) {
        coin.setPosition(newPos);
    }
    
private:
    sf::CircleShape coin;
};