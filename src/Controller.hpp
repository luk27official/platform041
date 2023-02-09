#pragma once

#include <SFML/Graphics.hpp>

#include "Level.hpp"
#include "Menu.hpp"
#include "Constants.hpp"
#include <memory>

/**
 * @brief A class that represents a window controller. Used to control the window - change menu/level, draw to the window, etc.
 */
class Controller {
    sf::RenderWindow window;
 
    /**
     * This string represents the current level. If it is "menu", the menu is drawn. Otherwise, the level with this name is drawn from the res/<levelName>.json file.
     * Watch out that this string is modified from other classes as well.
     */
    std::string currentLevel = "menu";

    std::shared_ptr<Level> level = nullptr;
    Menu menu;

    sf::Clock clock;
    float dt;

public:
    /*
    * @brief The main loop of the game. It handles the events, updates the level and draws to the window.
    */
    void main() {
        window.create(sf::VideoMode(Constants::get_window_width(), Constants::get_window_height()), "Platform041", sf::Style::Titlebar | sf::Style::Close);
        window.setKeyRepeatEnabled(false);
        window.setView(sf::View(sf::Vector2f(0, Constants::get_window_height() / 2.0), sf::Vector2f(Constants::get_window_width(), Constants::get_window_height())));
    
        while (window.isOpen()) {
    
            sf::Event event;
            dt = clock.restart().asSeconds();
            
            if(currentLevel == "menu") {
                if(level != nullptr) {
                    level = nullptr;
                }
                
                window.setView(sf::View(sf::Vector2f(0, Constants::get_window_height() / 2.0), sf::Vector2f(Constants::get_window_width(), Constants::get_window_height())));

                window.clear(sf::Color::White);

                menu.drawTo(window);

                menu.handleEvents(event, window, currentLevel);
                
                window.display();
            }

            else {
                if(level == nullptr) {
                    level = std::make_shared<Level>(currentLevel);
                }

                currentLevel = level->handleEvents(event, window, currentLevel);
        
                level->update(window, dt);

                window.clear(sf::Color::White);

                level->drawTo(window);

                window.display();
            }
        }
    }
};