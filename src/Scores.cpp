#include "../headers/Scores.hpp"

Scores::Scores() {
    //here we could possibly do something else when the font fails to load, but it does not really affect the functionality of the game
    //(the game will still run, but the menu text will not be displayed)
    if (!font.loadFromFile("res/vermin_vibes.ttf"))
    {
        std::cerr << "Error loading font" << std::endl;
    }
}

void Scores::createText(sf::RenderWindow &window, const std::string &displayText, int size, int x, int y,
                        const sf::Color color) {
    sf::Text text;
    text.setFont(font);
    text.setString(displayText);
    text.setCharacterSize(size);
    text.setFillColor(color);

    sf::FloatRect textRect = text.getLocalBounds();

    text.setOrigin((int)(textRect.left + textRect.width/2.0f), (int)(textRect.top + textRect.height/2.0f));
    text.setPosition(sf::Vector2f(x, y));

    texts.push_back(text);
    window.draw(text);
}

void Scores::drawTo(sf::RenderWindow &window) {
    if(texts.size() == 0) {
        createText(window, "Top scores", 80, 0, 50);
        createText(window, "Level", 40, -200, 150);
        createText(window, "Score", 40, 0, 150);
        createText(window, "Time", 40, 200, 150);

        std::ifstream f("res/scores.json");
        json data = json::parse(f);
        f.close();

        std::sort(data.begin(), data.end(), [](const json &a, const json &b){return a["score"] > b["score"];});
        int startingY = 220;

        for(auto& row : data) {
            std::string e = row["level"];
            //remove the quotes from the string
            e.erase(std::remove_if(e.begin(), e.end(), [](unsigned char x) { return x == '\"' || std::isalpha(x); }), e.end());
            createText(window, e, 40, -200, startingY);

            std::string e2 = row["score"];
            e2.erase(std::remove_if(e2.begin(), e2.end(), [](unsigned char x) { return x == '\"'; }), e2.end());
            createText(window, e2, 40, 0, startingY);

            std::string e3 = row["time"];
            e3.erase(std::remove_if(e3.begin(), e3.end(), [](unsigned char x) { return x == '\"'; }), e3.end());
            createText(window, e3, 40, 200, startingY);

            startingY += 50;
        }
    }
    else {
        for (int i = 0; i < texts.size(); i++) {
            window.draw(texts[i]);
        }
    }
}

void Scores::handleEvents(sf::Event &Event, sf::RenderWindow &window, std::string &currentLevel) {
    while (window.pollEvent(Event))
    {
        switch (Event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (Event.key.code == sf::Keyboard::Return || Event.key.code == sf::Keyboard::Space || Event.key.code == sf::Keyboard::Escape) {
                    texts.clear();
                    currentLevel = "menu";
                }
                break;
        }
    }
}

