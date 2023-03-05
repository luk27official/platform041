#pragma once

#include "SFML/Graphics.hpp"
#include "WallType.hpp"

/*
* @brief A class that represents a wall. Meant to be drawn to the screen. This class is meant to be inherited from. It is not meant to be used directly, but rather as a base class for other walls.
*/
class CustomWall {
protected:
    sf::RectangleShape shape;
    sf::Texture txt;

public:
    WallType type;

    CustomWall() = default;

    CustomWall(const CustomWall&) = delete;
    CustomWall& operator=(const CustomWall&) = delete;

    /*
    * @brief Draws the wall to the window
    */
    void drawTo(sf::RenderWindow &window);

    /*
    * @brief Returns the global bounds of the wall (used for collision detection)    
    */
    sf::FloatRect getGlobalBounds();

    /*
    * @brief Sets the position of the wall
    */
    void setPos(const sf::Vector2f newPos);

    /*
    * @brief Moves the wall by the given distance
    */
    void setSize(const sf::Vector2f size);

    /*
    * @brief Returns the rectangular shape of the wall (for collision detection and drawing)
    */
    sf::RectangleShape getShape();

    /*
    * @brief Sets the color of the wall. Used in case of a color change.
    */
    void setFillColor(const sf::Color color);
};