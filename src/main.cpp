#include <SFML/Graphics.hpp>
#include "Level.hpp"
 
int main() {
    sf::RenderWindow window;
 
    window.create(sf::VideoMode(1000, 600), "Platform041", sf::Style::Titlebar | sf::Style::Close);
    window.setKeyRepeatEnabled(true);
    window.setView(sf::View(sf::Vector2f(0, 300), sf::Vector2f(1000, 600)));

    Level level;
    sf::Clock clock;
    float dt;
 
    while (window.isOpen()) {
 
        sf::Event Event;

        //std::cout << "FPS: " << 1 / dt << std::endl;

        dt = clock.restart().asSeconds();

        level.handleEvents(Event, window);
 
        level.update(window, dt);
 
        window.clear(sf::Color::White);

        level.drawTo(window);

        window.display();
    }
}