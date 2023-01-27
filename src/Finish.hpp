#pragma once
 
#include <SFML/Graphics.hpp>
#include "CustomWall.hpp"
 
class Finish : public CustomWall {
public:
    Finish() {
        txt.loadFromFile("res/finish.png");
        shape.setSize({ 100, 100 });
        shape.setTexture(&txt);

        type = WallType::Finish;
    }
};