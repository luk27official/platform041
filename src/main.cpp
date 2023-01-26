#include <SFML/Graphics.hpp>
#include "Level.hpp"
 
int main() {
    sf::RenderWindow window;
 
    window.create(sf::VideoMode(1000, 600), "Platform041", sf::Style::Titlebar | sf::Style::Close);
    window.setKeyRepeatEnabled(true);

    Level level;
 
    while (window.isOpen()) {
 
        sf::Event Event;
        level.handleEvents(Event, window);
 
        level.update();
 
        window.clear();

        level.drawTo(window);

        window.display();
    }
}