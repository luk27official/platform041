//
// Created by luk27 on 05.03.2023.
//
#include "../headers/Finish.hpp"

Finish::Finish() {
    //currently not using a texture
    //txt.loadFromFile("res/finish.png");
    //shape.setTexture(&txt);
    setFillColor(sf::Color::Cyan);
    type = WallType::Finish;
}
