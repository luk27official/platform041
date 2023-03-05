#pragma once
 
#include "SFML/Graphics.hpp"
 
/**
 * @brief A class that represents a coin. Meant to be drawn to the screen.
 */
class Coin {
private:
    sf::Sprite sprite;
    sf::Texture txt;

public:
    bool isCollected = false;
    
    Coin();
 
    Coin(const Coin&) = delete;
    Coin& operator=(const Coin&) = delete;

    /*
    * @brief Draws the coin to the window
    */
    void drawTo(sf::RenderWindow &window);
    
    /*
    * @brief Returns the global bounds of the coin (used for collision detection)    
    */
    sf::FloatRect getGlobalBounds();
 
    /*
    * @brief Sets the position of the coin
    */
    void setPos(const sf::Vector2f newPos);
};