#pragma once

#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Coin.hpp"
#include "Enemy.hpp"
#include <vector>
#include <memory>

class Level {
    int score = 0;
    const int groundHeight = 500;
    
    //clock for jumping
    sf::Clock jumpClock;

    Player player;
    
    sf::RectangleShape ground;

    //std::vector<Coin> coinVec;
    std::vector<sf::RectangleShape> obstacleVec;
    std::vector<std::shared_ptr<Enemy>> enemyVec;

public:
    Level() {
        //Ground Object:
        ground.setSize({ 3000, 100 });
        float groundY = groundHeight + 32;
        ground.setFillColor(sf::Color::Green);
        ground.setPosition({ 0, groundY }); //32 is the height of the player sprite

        //obstacle object:
        sf::RectangleShape obstacle;
        obstacle.setSize({ 100, 100 });
        float obstacleY = groundHeight + 32 - 100;
        obstacle.setFillColor(sf::Color::Red);
        obstacle.setPosition({ 300, obstacleY }); //32 is the height of the player sprite

        obstacleVec.push_back(obstacle);

        sf::RectangleShape obstacle2;
        obstacle2.setSize({ 100, 20 });
        float obstacle2Y = groundHeight + 32 - 300;
        obstacle2.setFillColor(sf::Color::Red);
        obstacle2.setPosition({ 500, obstacle2Y }); //32 is the height of the player sprite
        obstacleVec.push_back(obstacle2);

        sf::RectangleShape obstacle3;
        obstacle3.setSize({ 100, 100 });
        float obstacle3Y = groundHeight + 32 - 100;
        obstacle3.setFillColor(sf::Color::Red);
        obstacle3.setPosition({ 700, obstacle3Y }); //32 is the height of the player sprite

        obstacleVec.push_back(obstacle3);

        //Coin Objects:
        /*
        Coin coin1;
        Coin coin2;

        coin1.setPos({ 50, 300 });
        coin2.setPos({ 100, 300 });

        coinVec.push_back(coin1);
        coinVec.push_back(coin2);
        */

        //Enemy Objects:
        std::shared_ptr<Enemy> enemy1 = std::make_shared<Enemy>();
        enemy1->setPos({ 700, 300 });

        enemyVec.push_back(enemy1);
    }

    void handlePlayerBottomObstacleCollision(float dt) {
        bool colliding = false;
        for (int i = 0; i < obstacleVec.size(); i++) {
            sf::RectangleShape o = obstacleVec.at(i);
            if (player.bottomObstacleCollision(o)) {
                colliding = true;
                break;
            }
        }

        //Gravity Logic:
        if(!colliding) {
            if (player.getY() < groundHeight && player.isJumping == false) {
                player.move({ 0, player.gravity * dt });
            }
        }
    }

    void handlePlayerRightObstacleCollision(sf::RenderWindow& window, float dt) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            bool colliding = false;
            for (int i = 0; i < obstacleVec.size(); i++) {
                sf::RectangleShape o = obstacleVec.at(i);
                if (player.rightObstacleCollision(o)) {
                    colliding = true;
                    break;
                }
            }
            if(!colliding) {
                player.move({ player.moveSpeed * dt, 0 });
                window.setView(sf::View(sf::Vector2f(player.getX(), 300), sf::Vector2f(1000, 600)));
            }
        }
    }

    void handlePlayerLeftObstacleCollision(sf::RenderWindow& window, float dt) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            bool colliding = false;
            for (int i = 0; i < obstacleVec.size(); i++) {
                sf::RectangleShape o = obstacleVec.at(i);
                if (player.leftObstacleCollision(o)) {
                    colliding = true;
                    break;
                }
            }
            if(!colliding && player.getX() > 0) {
                player.move({ -player.moveSpeed * dt, 0 });
                window.setView(sf::View(sf::Vector2f(player.getX(), 300), sf::Vector2f(1000, 600)));
            }
        }
    }

    void handlePlayerTopObstacleCollision(float dt) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if(!player.isJumping) {
                if(jumpClock.getElapsedTime().asSeconds() > player.resetJumpTime) {
                    player.isJumping = true;
                    jumpClock.restart();
                }
            }
        }

        if(player.isJumping) {
            bool colliding = false;
            for (int i = 0; i < obstacleVec.size(); i++) {
                sf::RectangleShape o = obstacleVec.at(i);
                if (player.topObstacleCollision(o)) {
                    colliding = true;
                    break;
                }
            }

            if(jumpClock.getElapsedTime().asSeconds() > player.resetJumpTime) {
                player.isJumping = false;
                jumpClock.restart();
            }

            if(!colliding && player.getY() > 0) {
                player.move({ 0, -player.moveSpeed * dt });
            }
        }
    }

    void handleEnemyObstacleCollision(std::shared_ptr<Enemy> e, float dt) {
        // bottom collision
        bool colliding = false;
        for (int i = 0; i < obstacleVec.size(); i++) {
            sf::RectangleShape o = obstacleVec.at(i);
            if (e->bottomObstacleCollision(o)) {
                colliding = true;
                break;
            }
        }

        //Gravity Logic:
        if(!colliding) {
            if (e->getY() < groundHeight) {
                e->move({ 0, e->gravity * dt });
            }
        }

        if(e->direction == Direction::Left) {
            //check left collision
            bool colliding = false;
            for (int i = 0; i < obstacleVec.size(); i++) {
                sf::RectangleShape o = obstacleVec.at(i);
                if (e->leftObstacleCollision(o)) {
                    colliding = true;
                    break;
                }
            }
            if(!colliding && e->getX() > 0) {
                e->move({ -e->moveSpeed * dt, 0 });
            }
            else {
                e->direction = Direction::Right;
            }
        }
        else if (e->direction == Direction::Right) {
            //check right collision
            bool colliding = false;
            for (int i = 0; i < obstacleVec.size(); i++) {
                sf::RectangleShape o = obstacleVec.at(i);
                if (e->rightObstacleCollision(o)) {
                    colliding = true;
                    break;
                }
            }
            if(!colliding) {
                e->move({ e->moveSpeed * dt, 0 });
            }
            else {
                e->direction = Direction::Left;
            }
        }

    }

    void update(sf::RenderWindow& window, float dt) {
        //Coin Logic:
        
        /*
        for (int i = 0; i < coinVec.size(); i++) {
            Coin c = coinVec.at(i);
            if (player.isCollidingWithCoin(c)) {
                coinVec.erase(coinVec.begin() + i);
                score++;
            }
        }
        */

        handlePlayerBottomObstacleCollision(dt); //gravity

        handlePlayerRightObstacleCollision(window, dt);

        handlePlayerLeftObstacleCollision(window, dt);

        handlePlayerTopObstacleCollision(dt); //jumping

        //Enemy Logic:
        for (int i = 0; i < enemyVec.size(); i++) {
            std::shared_ptr<Enemy> e = enemyVec.at(i);

            handleEnemyObstacleCollision(e, dt);

            if (player.isCollidingWithEnemy(e)) {
                player.die(window);
                break;
            }
        }
    }

    void drawTo(sf::RenderWindow& window) {
        /*
        for(int i = 0; i < coinVec.size(); i++) {
            coinVec.at(i).drawTo(window);
        }
        */

        for(int i = 0; i < obstacleVec.size(); i++) {
            window.draw(obstacleVec.at(i));
        }

        for(int i = 0; i < enemyVec.size(); i++) {
            enemyVec.at(i)->drawTo(window);
        }

        window.draw(ground);
        player.drawTo(window);
    }

    void handleEvents(sf::Event& event, sf::Window& window) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {
                    window.close();
                    break;
                }
    
                case sf::Event::KeyReleased:
                    if(event.key.code == sf::Keyboard::Up) {
                        player.isJumping = false;
                    }
                    break;
                
                default:
                    break;
            }
        }
    }
};
