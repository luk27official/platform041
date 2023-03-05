//
// Created by luk27 on 05.03.2023.
//
#include "../headers/Controller.hpp"

void Controller::main() {
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
                level = std::make_unique<Level>(currentLevel);
            }

            currentLevel = level->handleEvents(event, window, currentLevel);

            level->update(window, dt);

            window.clear(sf::Color::White);

            level->drawTo(window);

            window.display();
        }
    }
}
