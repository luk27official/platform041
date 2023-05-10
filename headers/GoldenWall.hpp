#pragma once

#include "SFML/Graphics.hpp"
#include "WallType.hpp"

/*
* @brief A class that represents a golden wall,
* but is incompatible with the CustomWall interface as we need to store additional
* information about the x,y positions separately and the rectangle shape has a different name.
*/
class GoldenWall {
protected:
    sf::RectangleShape rectangle;
    sf::Texture goldenTexture;

    float x;
    float y;

public:
    GoldenWall();

    virtual ~GoldenWall() { }

    void setX(float x);
    void setY(float y);

    float getX();
    float getY();
};