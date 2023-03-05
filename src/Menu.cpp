#include "../headers/Menu.hpp"

Menu::Menu() {
    selectedIdx = 0;

    //here we could possibly do something else when the font fails to load, but it does not really affect the functionality of the game
    //(the game will still run, but the menu text will not be displayed)
    if (!font.loadFromFile("res/vermin_vibes.ttf"))
    {
        std::cerr << "Error loading font" << std::endl;
    }
}

void Menu::createText(sf::RenderWindow &window, const std::string &displayText, int size, int x, int y,
                      const sf::Color color) {
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

void Menu::drawTo(sf::RenderWindow &window) {
    if(menuTexts.size() == 0) {
        createText(window, "Platform041", 100, 0, 50);
        createText(window, "Level 1", 40, 0, 200, sf::Color::Red);
        createText(window, "Level 2", 40, 0, 250);
        createText(window, "Scores", 40, 0, 400);
    }
    else {
        for (int i = 0; i < menuTexts.size(); i++) {
            window.draw(menuTexts[i]);
        }
    }
}

void Menu::handleEvents(sf::Event &Event, sf::RenderWindow &window, std::string &currentLevel) {
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
