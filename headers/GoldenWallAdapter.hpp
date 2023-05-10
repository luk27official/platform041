#pragma once

#include "SFML/Graphics.hpp"
#include "CustomWall.hpp"
#include "GoldenWall.hpp"
#include "WallType.hpp"

/*
* @brief An adapter for the GoldenWall class that represents a golden wall,
* but is incompatible with the CustomWall interface as we need to store additional
* information about the x,y positions separately and the rectangle shape has a different name.
* CustomWall is the target interface.
* GoldenWall is the adaptee.
* GoldenWallAdapter is the adapter.
* This is an example of the class adapter pattern.
*/
class GoldenWallAdapter : public CustomWall, private GoldenWall {
public:
    GoldenWallAdapter();

     /*
    * @brief Draws the wall to the window
    */
    virtual void drawTo(sf::RenderWindow &window);

    /*
    * @brief Returns the global bounds of the wall (used for collision detection)    
    */
    virtual sf::FloatRect getGlobalBounds();

    /*
    * @brief Sets the position of the wall
    */
    virtual void setPos(const sf::Vector2f newPos);

    /*
    * @brief Moves the wall by the given distance
    */
    virtual void setSize(const sf::Vector2f size);

    /*
    * @brief Returns the rectangular shape of the wall (for collision detection and drawing)
    */
    virtual sf::RectangleShape getShape();

    /*
    * @brief Sets the color of the wall. Used in case of a color change.
    */
    virtual void setFillColor(const sf::Color color);
};