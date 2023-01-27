#pragma once

#include <SFML/Graphics.hpp>

enum class WallType {
    ClassicWall,
    KillingObstacle,
    Finish
};

class CustomWall {
protected:
    sf::RectangleShape shape;
    sf::Texture txt;

public:
    WallType type;

    void drawTo(sf::RenderWindow &window) {
        window.draw(shape);
    }

    sf::FloatRect getGlobalBounds() {
        return shape.getGlobalBounds();
    }

    void setPos(sf::Vector2f newPos) {
        shape.setPosition(newPos);
    }

    void setSize(sf::Vector2f size) {
        shape.setSize(size);
    }

    sf::RectangleShape getShape() {
        return shape;
    }
};