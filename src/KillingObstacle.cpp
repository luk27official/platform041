#include "../headers/KillingObstacle.hpp"

KillingObstacle::KillingObstacle() {
    type = WallType::KillingObstacle;
    setFillColor(sf::Color::Red);
}
