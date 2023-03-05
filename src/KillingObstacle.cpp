//
// Created by luk27 on 05.03.2023.
//
#include "../headers/KillingObstacle.hpp"

KillingObstacle::KillingObstacle() {
    type = WallType::KillingObstacle;
    setFillColor(sf::Color::Red);
}
