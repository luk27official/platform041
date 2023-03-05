#pragma once
 
#include <SFML/Graphics.hpp>
 
/**
 * @brief A class that represents a coin. Meant to be drawn to the screen.
 */
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
 
    /*
    * @brief Draws the coin to the window
    */
    void drawTo(sf::RenderWindow &window) {
        window.draw(sprite);
    }
    
    /*
    * @brief Returns the global bounds of the coin (used for collision detection)    
    */
    sf::FloatRect getGlobalBounds() {
        return sprite.getGlobalBounds();
    }
 
    /*
    * @brief Sets the position of the coin
    */
    void setPos(const sf::Vector2f newPos) {
        sprite.setPosition(newPos);
    }

};