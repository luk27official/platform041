#pragma once

#include <SFML/Graphics.hpp>
#include "CustomWall.hpp"

class ClassicWall : public CustomWall {
public:
    ClassicWall() {
        //txt.loadFromFile("res/classicWall.png");

        //shape.set
        //shape.setSize({ 100, 100 });
        //shape.setTexture(&txt);
        type = WallType::ClassicWall;
    }

    void setFillColor(const sf::Color color) {
        shape.setFillColor(color);
    }
};