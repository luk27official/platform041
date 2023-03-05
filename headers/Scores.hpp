#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <memory>
#include <fstream>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

class Scores {
private:
    sf::Font font;
    std::vector<sf::Text> texts;

public:

    Scores();

    /*
    * @brief Creates a text object with the given size, x, y and color; adds it to the menu vector and draws it to the window
    */
    void createText(sf::RenderWindow &window, const std::string &displayText, int size, int x, int y, const sf::Color color = sf::Color::Black);

    /*
    * @brief Draws the scores to the window
    */
    void drawTo(sf::RenderWindow &window);

    /*
    * @brief Handles the events of the menu (keyboard strokes). Allows the user to return to the menu
    */
    void handleEvents(sf::Event &Event, sf::RenderWindow &window, std::string &currentLevel);
};