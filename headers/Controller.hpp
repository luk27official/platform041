#pragma once

#include "SFML/Graphics.hpp"

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

    std::unique_ptr<Level> level = nullptr;
    Menu menu;

    sf::Clock clock;
    float dt;

public:
    /*
    * @brief The main loop of the game. It handles the events, updates the level and draws to the window.
    */
    void main();
};