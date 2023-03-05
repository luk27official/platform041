#include "../headers/Coin.hpp"

Coin::Coin() {
    txt.loadFromFile("res/coin.png");
    sprite.setTexture(txt);
}

void Coin::drawTo(sf::RenderWindow &window) {
    window.draw(sprite);
}

void Coin::setPos(const sf::Vector2f newPos) {
    sprite.setPosition(newPos);
}

sf::FloatRect Coin::getGlobalBounds() {
    return sprite.getGlobalBounds();
}
