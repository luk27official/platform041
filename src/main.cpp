#include <SFML/Graphics.hpp>
#include "Level.hpp"
 
int main() {
    sf::RenderWindow window;
 
    window.create(sf::VideoMode(1000, 600), "Platform041", sf::Style::Titlebar | sf::Style::Close);
    window.setKeyRepeatEnabled(true);
    window.setView(sf::View(sf::Vector2f(0, 300), sf::Vector2f(1000, 600)));

    Level level;
 
    while (window.isOpen()) {
 
        sf::Event Event;
        level.handleEvents(Event, window);
 
        level.update(window);
 
        window.clear();

        level.drawTo(window);

        window.display();
    }
}