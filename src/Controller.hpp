#pragma once

#include <SFML/Graphics.hpp>

#include "Level.hpp"
#include "Menu.hpp"
#include <memory>

class Controller {
    sf::RenderWindow window;
 
    std::string currentLevel = "menu";

    std::shared_ptr<Level> level = nullptr;
    Menu menu;

    sf::Clock clock;
    float dt;

public:
    void main() {
        window.create(sf::VideoMode(1000, 600), "Platform041", sf::Style::Titlebar | sf::Style::Close);
        window.setKeyRepeatEnabled(true);
        window.setView(sf::View(sf::Vector2f(0, 300), sf::Vector2f(1000, 600)));
    
        while (window.isOpen()) {
    
            sf::Event event;
            dt = clock.restart().asSeconds();
            
            if(currentLevel == "menu") {
                if(level != nullptr) {
                    level = nullptr;
                }
                
                window.setView(sf::View(sf::Vector2f(0, 300), sf::Vector2f(1000, 600)));

                window.clear(sf::Color::White);

                menu.drawTo(window);

                menu.handleEvents(event, window, currentLevel);
                
                window.display();
            }

            else {
                if(level == nullptr) {
                    level = std::make_shared<Level>();
                }

                level->handleEvents(event, window);
        
                currentLevel = level->update(window, dt, currentLevel);

                window.clear(sf::Color::White);

                level->drawTo(window);

                window.display();
            }

            //std::cout << "FPS: " << 1 / dt << std::endl;
        }
    }
};