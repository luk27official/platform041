#pragma once
 
#include <SFML/Graphics.hpp>
#include "CustomWall.hpp"
 
class Finish : public CustomWall {
public:
    Finish() {
        //txt.loadFromFile("res/finish.png");
        //shape.setTexture(&txt);
        setFillColor(sf::Color::Cyan); // TODO: Change to finish texture?
        type = WallType::Finish;
    }

    void setFillColor(const sf::Color color) {
        shape.setFillColor(color);
    }
};