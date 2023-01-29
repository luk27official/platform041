#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Menu {
private:
    sf::Font font;
    std::vector<sf::Text> menuTexts;
    int selectedIdx;

public:
    Menu() {
        selectedIdx = 0;

        if (!font.loadFromFile("res/vermin_vibes.ttf"))
        {
            std::cout << "Error loading font" << std::endl;
        }
    }

    void createText(sf::RenderWindow &window, const std::string& displayText, int size, int x, int y) {
        sf::Text text;
        text.setFont(font);
        text.setString(displayText);
        text.setCharacterSize(size);
        text.setFillColor(sf::Color::Black);

        sf::FloatRect textRect = text.getLocalBounds();

        text.setOrigin((int)(textRect.left + textRect.width/2.0f), (int)(textRect.top + textRect.height/2.0f));
        text.setPosition(sf::Vector2f(x, y));

        menuTexts.push_back(text);
        window.draw(text);
    }

    void drawTo(sf::RenderWindow &window) {
        if(menuTexts.size() == 0) {
            createText(window, "Platform041", 100, 0, 50);
            createText(window, "Level 1", 40, 0, 200);
            menuTexts[1].setFillColor(sf::Color::Red);
            createText(window, "Level 2", 40, 0, 250);
        }
        else {
            for (int i = 0; i < menuTexts.size(); i++) {
                window.draw(menuTexts[i]);
            }
        }
    }

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
                        std::cout << "Selected: " << menuTexts[selectedIdx+1].getString().toAnsiString() << std::endl;
                        currentLevel = menuTexts[selectedIdx+1].getString().toAnsiString();
                    }
                    break;
            }
        }
    }
};