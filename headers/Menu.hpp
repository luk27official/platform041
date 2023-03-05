#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <memory>

/*
* @brief A class that represents a menu. Meant to be drawn to the screen.
*/
class Menu {
private:
    sf::Font font;
    std::vector<sf::Text> menuTexts;
    int selectedIdx;

public:
    Menu();

    /*
    * @brief Creates a text object with the given size, x, y and color; adds it to the menuTexts vector and draws it to the window
    */
    void createText(sf::RenderWindow &window, const std::string& displayText, int size, int x, int y, const sf::Color color = sf::Color::Black);

    /*
    * @brief Draws the menu to the window
    */
    void drawTo(sf::RenderWindow &window);

    /*
    * @brief Handles the events of the menu (keyboard strokes). Allows the user to select the wanted level
    */
    void handleEvents(sf::Event &Event, sf::RenderWindow &window, std::string& currentLevel);
};