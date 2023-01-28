#pragma once

#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "Coin.hpp"
#include "Enemy.hpp"
#include "CustomWall.hpp"
#include "ClassicWall.hpp"
#include "Finish.hpp"
#include "KillingObstacle.hpp"
#include "Direction.hpp"

#include <vector>
#include <memory>

class Level {
    int score = 0;
    const int groundHeight = 500;
    const int playerHeight = 32;
    
    //clock for jumping
    sf::Clock jumpClock;

    Player player;
    
    sf::RectangleShape ground;

    std::vector<std::shared_ptr<Coin>> coinVec;
    std::vector<std::shared_ptr<CustomWall>> obstacleVec;
    std::vector<std::shared_ptr<Enemy>> enemyVec;


public:
    Level() {
        //Ground Object:
        ground.setSize({ 3000, 100 });
        float groundY = groundHeight + playerHeight;
        ground.setFillColor(sf::Color::Green);
        ground.setPosition({ 0, groundY }); //32 is the height of the player sprite

        //obstacle object:
        std::shared_ptr<ClassicWall> obstacle = std::make_shared<ClassicWall>();

        obstacle->setSize({ 100, 100 });
        float obstacleY = groundHeight + playerHeight - 100;
        obstacle->setPos({ 300, obstacleY }); //playerHeight is the height of the player sprite

        obstacleVec.push_back(obstacle);

        std::shared_ptr<ClassicWall> obstacle2 = std::make_shared<ClassicWall>();
        obstacle2->setSize({ 100, 20 });
        float obstacle2Y = groundHeight + playerHeight - 300;
        obstacle2->setPos({ 500, obstacle2Y }); //playerHeight is the height of the player sprite
        
        obstacleVec.push_back(obstacle2);

        std::shared_ptr<ClassicWall> obstacle3 = std::make_shared<ClassicWall>();
        obstacle3->setSize({ 100, 100 });
        float obstacle3Y = groundHeight + playerHeight - 100;
        obstacle3->setPos({ 700, obstacle3Y }); //playerHeight is the height of the player sprite

        obstacleVec.push_back(obstacle3);

        std::shared_ptr<KillingObstacle> kill1 = std::make_shared<KillingObstacle>();
        kill1->setSize({ 50, 20 });
        float kill1Y = groundHeight + playerHeight - 20;
        kill1->setPos({ 900, kill1Y }); //playerHeight is the height of the player sprite

        obstacleVec.push_back(kill1);

        //Coin Objects:
        std::shared_ptr<Coin> coin1 = std::make_shared<Coin>();
        coin1->setPos({ 50, 300 });
        
        std::shared_ptr<Coin> coin2 = std::make_shared<Coin>();
        coin2->setPos({ 100, 300 });

        coinVec.push_back(coin1);
        coinVec.push_back(coin2);

        //Enemy Objects:
        std::shared_ptr<Enemy> enemy1 = std::make_shared<Enemy>(800, 150, "res/enemy.png");
        enemy1->setPos({ 700, 300 });

        enemyVec.push_back(enemy1);


        std::shared_ptr<Enemy> enemy2 = std::make_shared<Enemy>(800, 200, "res/enemy2.png");
        enemy2->setPos({ 550, 100 });

        enemyVec.push_back(enemy2);

        // Finish 
        std::shared_ptr<Finish> finish = std::make_shared<Finish>();
        finish->setPos({ 1000, 0 });
        finish->setSize({ 100, (float)(groundHeight + playerHeight) });
        obstacleVec.push_back(finish);

    }

    void gameWin() {
        std::cout << "You win!" << std::endl;
    }

    void handlePlayerBottomObstacleCollision(sf::RenderWindow& window, float dt) {
        bool colliding = false;
        for (int i = 0; i < obstacleVec.size(); i++) {
            sf::RectangleShape o = obstacleVec.at(i)->getShape();
            if (player.bottomObstacleCollision(o)) {
                switch(obstacleVec.at(i)->type) {
                    case WallType::ClassicWall:
                        colliding = true;
                        break;
                    case WallType::KillingObstacle:
                        player.die(window);
                        break;
                    case WallType::Finish:
                        gameWin();
                        break;
                }
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
            player.direction = Direction::Right;
            bool colliding = false;
            for (int i = 0; i < obstacleVec.size(); i++) {
                sf::RectangleShape o = obstacleVec.at(i)->getShape();
                if (player.rightObstacleCollision(o)) {
                    switch(obstacleVec.at(i)->type) {
                        case WallType::ClassicWall:
                            colliding = true;
                            break;
                        case WallType::KillingObstacle:
                            player.die(window);
                            break;
                        case WallType::Finish:
                            gameWin();
                            break;
                    }
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
            player.direction = Direction::Left;
            bool colliding = false;
            for (int i = 0; i < obstacleVec.size(); i++) {
                sf::RectangleShape o = obstacleVec.at(i)->getShape();
                if (player.leftObstacleCollision(o)) {
                    switch(obstacleVec.at(i)->type) {
                        case WallType::ClassicWall:
                            colliding = true;
                            break;
                        case WallType::KillingObstacle:
                            player.die(window);
                            break;
                        case WallType::Finish:
                            gameWin();
                            break;
                    }
                    break;
                }
            }
            if(!colliding && player.getX() > 0) {
                player.move({ -player.moveSpeed * dt, 0 });
                window.setView(sf::View(sf::Vector2f(player.getX(), 300), sf::Vector2f(1000, 600)));
            }
        }
    }

    void handlePlayerTopObstacleCollision(sf::RenderWindow& window, float dt) {
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
                sf::RectangleShape o = obstacleVec.at(i)->getShape();
                if (player.topObstacleCollision(o)) {
                    switch(obstacleVec.at(i)->type) {
                        case WallType::ClassicWall:
                            colliding = true;
                            break;
                        case WallType::KillingObstacle:
                            player.die(window);
                            break;
                        case WallType::Finish:
                            gameWin();
                            break;
                    }
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
            sf::RectangleShape o = obstacleVec.at(i)->getShape();
            if (e->bottomObstacleCollision(o)) {
                colliding = true;
                break;
            }
        }

        //Gravity Logic:
        if(!colliding) {
            if (e->getY() < groundHeight - e->getGlobalBounds().height + playerHeight) {
                e->move({ 0, e->gravity * dt });
            }
        }

        if(e->direction == Direction::Left) {
            //check left collision
            bool colliding = false;
            for (int i = 0; i < obstacleVec.size(); i++) {
                sf::RectangleShape o = obstacleVec.at(i)->getShape();
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
                sf::RectangleShape o = obstacleVec.at(i)->getShape();
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

    void handleEnemyLogic(sf::RenderWindow& window, float dt) {
        for (int i = 0; i < enemyVec.size(); i++) {
            std::shared_ptr<Enemy> e = enemyVec.at(i);

            handleEnemyObstacleCollision(e, dt);

            if (player.isCollidingWithEnemy(e)) {
                player.die(window);
                break;
            }
        }
    }

    void handleCoinLogic() {
        for (int i = 0; i < coinVec.size(); i++) {
            std::shared_ptr<Coin> c = coinVec.at(i);
            if (player.isCollidingWithCoin(c)) {
                coinVec.erase(coinVec.begin() + i);
                score++;
                std::cout << "Coin collected! Current score: " << score << std::endl;
            }
        }
    }

    void handlePlayerLogic(sf::RenderWindow& window, float dt) {
        handlePlayerBottomObstacleCollision(window, dt); //gravity

        handlePlayerRightObstacleCollision(window, dt);

        handlePlayerLeftObstacleCollision(window, dt);

        handlePlayerTopObstacleCollision(window, dt); //jumping
    }

    void update(sf::RenderWindow& window, float dt) {
        handleCoinLogic();

        handlePlayerLogic(window, dt);

        handleEnemyLogic(window, dt);        
    }

    void drawTo(sf::RenderWindow& window) {
        for(int i = 0; i < coinVec.size(); i++) {
            coinVec.at(i)->drawTo(window);
        }

        for(int i = 0; i < obstacleVec.size(); i++) {
            window.draw(obstacleVec.at(i)->getShape());
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
