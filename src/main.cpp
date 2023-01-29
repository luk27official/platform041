#include <SFML/Graphics.hpp>
#include "Level.hpp"
#include "Menu.hpp"
 
int main() {
    sf::RenderWindow window;

    std::string currentLevel = "menu";
 
    window.create(sf::VideoMode(1000, 600), "Platform041", sf::Style::Titlebar | sf::Style::Close);
    window.setKeyRepeatEnabled(true);
    window.setView(sf::View(sf::Vector2f(0, 300), sf::Vector2f(1000, 600)));

    Level level;
    Menu menu;

    sf::Clock clock;
    float dt;
 
    while (window.isOpen()) {
 
        sf::Event Event;
        dt = clock.restart().asSeconds();
        
        if(currentLevel == "menu") {
            window.clear(sf::Color::White);

            menu.handleEvents(Event, window, currentLevel);

            menu.drawTo(window);

            window.display();
        }

        else {
            level.handleEvents(Event, window);
    
            level.update(window, dt);
    
            window.clear(sf::Color::White);

            level.drawTo(window);

            window.display();
        }

        //std::cout << "FPS: " << 1 / dt << std::endl;
    }
}