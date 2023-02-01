#pragma once

#include <SFML/Graphics.hpp>
#include "CustomWall.hpp"

/*
* @brief A class that represents a wall that kills the player. Meant to be drawn to the screen.
*/
class KillingObstacle : public CustomWall {
public:
    KillingObstacle() {
        type = WallType::KillingObstacle;
        setFillColor(sf::Color::Red);
    }
};
