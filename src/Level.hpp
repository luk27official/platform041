#pragma once

#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Coin.hpp"

class Level {
    int score = 0;
    const int groundHeight = 500;
    const float gravitySpeed = 0.3;
    const float moveSpeed = 0.1;
    bool isJumping = false;
    
    Player player;
    
    sf::RectangleShape ground;

    std::vector<Coin> coinVec;
    std::vector<sf::RectangleShape> obstacleVec;

public:
    Level() {
        //Player Object:
        //player.setPos({ 50, 700 });
    
        //Ground Object:
        ground.setSize({ 1000, 100 });
        ground.setFillColor(sf::Color::Green);
        ground.setPosition({ 0, groundHeight + 32 }); //32 is the height of the player sprite

        //obstacle object:
        sf::RectangleShape obstacle;
        obstacle.setSize({ 100, 100 });
        obstacle.setFillColor(sf::Color::Red);
        obstacle.setPosition({ 300, groundHeight + 32 - 100 }); //32 is the height of the player sprite

        obstacleVec.push_back(obstacle);

        sf::RectangleShape obstacle2;
        obstacle2.setSize({ 100, 20 });
        obstacle2.setFillColor(sf::Color::Red);
        obstacle2.setPosition({ 500, groundHeight + 32 - 300 }); //32 is the height of the player sprite

        obstacleVec.push_back(obstacle2);

        //Coin Objects:
        Coin coin1;
        Coin coin2;

        coin1.setPos({ 50, 300 });
        coin2.setPos({ 100, 300 });

        coinVec.push_back(coin1);
        coinVec.push_back(coin2);
    }

    void update() {
        //Coin Logic:
        for (int i = 0; i < coinVec.size(); i++) {
            Coin c = coinVec.at(i);
            if (player.isCollidingWithCoin(c)) {
                coinVec.erase(coinVec.begin() + i);
                score++;
            }
        }

        //Obstacle Logic: bottom collision
        bool colliding = false;
        for (int i = 0; i < obstacleVec.size(); i++) {
            sf::RectangleShape o = obstacleVec.at(i);
            if (player.collidingOnTheTop(o)) {
                colliding = true;
                break;
            }
        }

        //Gravity Logic:
        if(!colliding) {
            if (player.getY() < groundHeight && isJumping == false) {
                player.move({ 0, gravitySpeed });
            }
        }

        //Obstacle Logic: right collision
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            colliding = false;
            for (int i = 0; i < obstacleVec.size(); i++) {
                sf::RectangleShape o = obstacleVec.at(i);
                if (player.collidingOnTheLeft(o)) {
                    colliding = true;
                    break;
                }
            }
            if(!colliding) {
                player.move({ moveSpeed, 0 });
            }
        }

        //Obstacle Logic: left collision
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            colliding = false;
            for (int i = 0; i < obstacleVec.size(); i++) {
                sf::RectangleShape o = obstacleVec.at(i);
                if (player.collidingOnTheRight(o)) {
                    colliding = true;
                    break;
                }
            }
            if(!colliding && player.getX() > 0) {
                player.move({ -moveSpeed, 0 });
            }
        }

        //Obstacle Logic: top collision
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            colliding = false;
            for (int i = 0; i < obstacleVec.size(); i++) {
                sf::RectangleShape o = obstacleVec.at(i);
                if (player.collidingOnTheBottom(o)) {
                    colliding = true;
                    break;
                }
            }
            if(!colliding && player.getY() > 0) {
                isJumping = true;
                player.move({ 0, -moveSpeed });
            }
        }
    }

    void drawTo(sf::RenderWindow& window) {
        for(int i = 0; i < coinVec.size(); i++) {
            coinVec.at(i).drawTo(window);
        }

        for(int i = 0; i < obstacleVec.size(); i++) {
            window.draw(obstacleVec.at(i));
        }

        window.draw(ground);
        player.drawTo(window);
    }

    void handleEvents(sf::Event& event, sf::Window& window) {
        //Event Loop:
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
    
                case sf::Event::KeyReleased:
                    isJumping = false;
            }
        }
    }
};
