#include "../headers/Finish.hpp"

Finish::Finish() {
    //currently not using a texture
    //txt.loadFromFile("res/finish.png");
    //shape.setTexture(&txt);
    setFillColor(sf::Color::Cyan);
    type = WallType::Finish;
}
