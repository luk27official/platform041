#pragma once

#include <SFML/Graphics.hpp>
#include "CustomWall.hpp"

class KillingObstacle : public CustomWall {
public:
    KillingObstacle() {
        type = WallType::KillingObstacle;
        setFillColor(sf::Color::Red);
    }

    void setFillColor(const sf::Color color) {
        shape.setFillColor(color);
    }
};
