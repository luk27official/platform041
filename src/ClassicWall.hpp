#pragma once

#include <SFML/Graphics.hpp>
#include "CustomWall.hpp"

/**
 * @brief A class that represents a classic wall. Meant to be drawn to the screen.
 */
class ClassicWall : public CustomWall {
public:
    ClassicWall() {
        type = WallType::ClassicWall;
        setFillColor(sf::Color::Black);
    }
};