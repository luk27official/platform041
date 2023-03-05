#pragma once

#include <SFML/Graphics.hpp>
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
    Menu() {
        selectedIdx = 0;

        //here we could possibly do something else when the font fails to load, but it does not really affect the functionality of the game
        //(the game will still run, but the menu text will not be displayed) 
        if (!font.loadFromFile("res/vermin_vibes.ttf"))
        {
            std::cerr << "Error loading font" << std::endl;
        }
    }

    /*
    * @brief Creates a text object with the given size, x, y and color; adds it to the menuTexts vector and draws it to the window
    */
    void createText(sf::RenderWindow &window, const std::string& displayText, int size, int x, int y, const sf::Color color = sf::Color::Black) {
        sf::Text text;
        text.setFont(font);
        text.setString(displayText);
        text.setCharacterSize(size);
        text.setFillColor(color);

        sf::FloatRect textRect = text.getLocalBounds();

        text.setOrigin((int)(textRect.left + textRect.width/2.0f), (int)(textRect.top + textRect.height/2.0f));
        text.setPosition(sf::Vector2f(x, y));

        menuTexts.push_back(text);
        window.draw(text);
    }

    /*
    * @brief Draws the menu to the window
    */
    void drawTo(sf::RenderWindow &window) {
        if(menuTexts.size() == 0) {
            createText(window, "Platform041", 100, 0, 50);
            createText(window, "Level 1", 40, 0, 200, sf::Color::Red);
            createText(window, "Level 2", 40, 0, 250);
        }
        else {
            for (int i = 0; i < menuTexts.size(); i++) {
                window.draw(menuTexts[i]);
            }
        }
    }

    /*
    * @brief Handles the events of the menu (keyboard strokes). Allows the user to select the wanted level
    */
    void handleEvents(sf::Event &Event, sf::RenderWindow &window, std::string& currentLevel) {
        while (window.pollEvent(Event))
        {
            switch (Event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (Event.key.code == sf::Keyboard::Down) {
                        menuTexts[selectedIdx+1].setFillColor(sf::Color::Black);
                        selectedIdx = (selectedIdx + 1) % (menuTexts.size() - 1);
                        menuTexts[selectedIdx+1].setFillColor(sf::Color::Red);
                    }
                    else if (Event.key.code == sf::Keyboard::Up) {
                        menuTexts[selectedIdx+1].setFillColor(sf::Color::Black);
                        selectedIdx = (selectedIdx - 1) % (menuTexts.size() - 1);
                        menuTexts[selectedIdx+1].setFillColor(sf::Color::Red);
                    }
                    else if (Event.key.code == sf::Keyboard::Return || Event.key.code == sf::Keyboard::Space) {
                        //on space/enter: gets the level name, removes spaces, makes it lowercase and sets it to currentLevel
                        std::string level = menuTexts[selectedIdx+1].getString().toAnsiString();
                        std::transform(level.begin(), level.end(), level.begin(), [](unsigned char c){ return std::tolower(c); });
                        level.erase(std::remove_if(level.begin(), level.end(), [](unsigned char x) { return std::isspace(x); }), level.end());
                        currentLevel = level;
                    }
                    break;
            }
        }
    }
};