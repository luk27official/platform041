#pragma once
 
#include <SFML/Graphics.hpp>
#include "CustomWall.hpp"

/*
* @brief A class that represents a finish area. Meant to be drawn to the screen.
*/
class Finish : public CustomWall {
public:
    Finish() {
        //currently not using a texture
        //txt.loadFromFile("res/finish.png");
        //shape.setTexture(&txt);
        setFillColor(sf::Color::Cyan);
        type = WallType::Finish;
    }
};