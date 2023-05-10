#include "../headers/GoldenWall.hpp"

GoldenWall::GoldenWall() {
    goldenTexture.loadFromFile("res/golden_wall.png");
    rectangle.setTexture(&goldenTexture);
}

void GoldenWall::setX(float x) {
    this->x = x;
}

void GoldenWall::setY(float y) {
    this->y = y;
}

float GoldenWall::getX() {
    return x;
}

float GoldenWall::getY() {
    return y;
}