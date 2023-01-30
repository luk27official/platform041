#pragma once

#include <SFML/Graphics.hpp>

#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "Player.hpp"
#include "Coin.hpp"
#include "Enemy.hpp"
#include "CustomWall.hpp"
#include "ClassicWall.hpp"
#include "Finish.hpp"
#include "KillingObstacle.hpp"
#include "Direction.hpp"
#include "Bullet.hpp"

#include <vector>
#include <memory>
#include <iostream>

class Level {
    int score = 0;
    const float groundHeight = 500;
    float levelWidth = 3000; //defined by the json

    const float playerHeight = 32;
    const float playerWidth = 32;

    sf::Clock jumpClock;
    sf::Clock shootClock;
    sf::Clock levelClock;

    Player player;
    
    sf::RectangleShape ground;

    std::vector<std::shared_ptr<Coin>> coinVec;
    std::vector<std::shared_ptr<CustomWall>> obstacleVec;
    std::vector<std::shared_ptr<Enemy>> enemyVec;
    std::vector<std::shared_ptr<Bullet>> bulletVec;
    std::vector<sf::Text> textVec;

    sf::Font font;

    std::string nextLevel;

public:

    void parseGround(json& data) {

        int width = data["width"];
        int height = data["height"];

        int x = data["x"];
        int y = data["y"];
        
        int r = data["color"]["r"];
        int g = data["color"]["g"];
        int b = data["color"]["b"];

        ground.setSize({ width, height });
        ground.setFillColor(sf::Color(r, g, b));
        ground.setPosition({ x, y + playerHeight });
    }

    void parseJson(std::string& path) {
        std::string actualPath = "res/" + path + ".json";

        std::cout << actualPath << std::endl;

        std::ifstream f(actualPath);
        json data = json::parse(f);

        for(auto& element : data) {
            std::string e = element["type"];
            e.erase(std::remove_if(e.begin(), e.end(), [](unsigned char x) { return x == '\"'; }), e.end());

            if(e == "ground") {
                parseGround(element);
            }
        }

    }

    Level(std::string& path) {
        if (!font.loadFromFile("res/vermin_vibes.ttf"))
        {
            std::cout << "Error loading font" << std::endl;
        }

        parseJson(path);

        //Ground Object:
        /*
        ground.setSize({ levelWidth, 100 });
        float groundY = groundHeight + playerHeight;
        ground.setFillColor(sf::Color::Green);
        ground.setPosition({ 0, groundY }); //32 is the height of the player sprite
        */

        //obstacle object:
        std::shared_ptr<ClassicWall> obstacle = std::make_shared<ClassicWall>();

        obstacle->setSize({ 100, 100 });
        float obstacleY = 400 + playerHeight;
        obstacle->setPos({ 300, obstacleY }); //playerHeight is the height of the player sprite

        obstacleVec.push_back(obstacle);

        std::shared_ptr<ClassicWall> obstacle2 = std::make_shared<ClassicWall>();
        obstacle2->setSize({ 100, 20 });
        float obstacle2Y = 200 + playerHeight;
        obstacle2->setPos({ 500, obstacle2Y }); //playerHeight is the height of the player sprite
        
        obstacleVec.push_back(obstacle2);

        std::shared_ptr<ClassicWall> obstacle3 = std::make_shared<ClassicWall>();
        obstacle3->setSize({ 100, 100 });
        float obstacle3Y = 400 + playerHeight;
        obstacle3->setPos({ 700, obstacle3Y }); //playerHeight is the height of the player sprite

        obstacleVec.push_back(obstacle3);

        //Killing Obstacle Object:
        std::shared_ptr<KillingObstacle> kill1 = std::make_shared<KillingObstacle>();
        kill1->setSize({ 50, 20 });
        float kill1Y = 480 + playerHeight;
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

    void gameWin(sf::RenderWindow &window) {
        std::cout << "You win!" << std::endl;

        window.setView(sf::View(sf::Vector2f(0, 300), sf::Vector2f(1000, 600)));
        std::string displayText = "You win! Score: " + std::to_string(score) + ", Time (s): " + std::to_string(levelClock.getElapsedTime().asSeconds());
        sf::Text text = createText(window, displayText, 50, 0, 300, sf::Color(0, 155, 0));

        sf::Clock clock;

        while(clock.getElapsedTime().asSeconds() < 3) {
            window.clear(sf::Color::White);
            window.draw(text);
            sleep(sf::milliseconds(100));
            window.display();
        }

        nextLevel = "menu";
    }

    sf::Text createText(sf::RenderWindow &window, const std::string& displayText, int size, int x, int y, sf::Color color = sf::Color::Black) {
        sf::Text text;
        text.setFont(font);
        text.setString(displayText);
        text.setCharacterSize(size);
        text.setFillColor(color);

        sf::FloatRect textRect = text.getLocalBounds();

        text.setOrigin((int)(textRect.left + textRect.width/2.0f), (int)(textRect.top + textRect.height/2.0f));
        text.setPosition(sf::Vector2f(x, y));

        return text;
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
                        gameWin(window);
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
                            gameWin(window);
                            break;
                    }
                    break;
                }
            }
            if(!colliding && player.getX() < levelWidth - playerWidth) {
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
                            gameWin(window);
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
                            gameWin(window);
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

    void handlePlayerShootLogic(sf::RenderWindow& window, float dt) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if(shootClock.getElapsedTime().asSeconds() > player.resetShootTime) {
                std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>();
                bullet->setPos({ (float)player.getX(), (float)(player.getY() + playerHeight / 2) });
                bullet->direction = player.direction;
                bulletVec.push_back(bullet);
                shootClock.restart();
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
            if(!colliding && e->getX() < levelWidth - e->getGlobalBounds().width) {
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

    void handleBulletLogic(sf::RenderWindow& window, float dt) {
        for (int i = 0; i < bulletVec.size(); i++) {
            std::shared_ptr<Bullet> b = bulletVec.at(i);

            //check collision with enemy
            for (int j = 0; j < enemyVec.size(); j++) {
                std::shared_ptr<Enemy> e = enemyVec.at(j);
                if (b->isCollidingWithEnemy(e)) {
                    enemyVec.erase(enemyVec.begin() + j);
                    bulletVec.erase(bulletVec.begin() + i);
                    break;
                }
            }

            //check collision with obstacle
            for (int j = 0; j < obstacleVec.size(); j++) {
                sf::RectangleShape o = obstacleVec.at(j)->getShape();

                if (b->isCollidingWithObstacle(o)) {
                    bulletVec.erase(bulletVec.begin() + i);
                    break;
                }
            }

            if(b->direction == Direction::Left) {
                b->move({ -b->bulletSpeed * dt, 0 });
            }
            else if (b->direction == Direction::Right) {
                b->move({ b->bulletSpeed * dt, 0 });
            }

            if (b->getX() > levelWidth || b->getX() < 0) {
                bulletVec.erase(bulletVec.begin() + i);
            }
        }
    }

    void handlePlayerLogic(sf::RenderWindow& window, float dt) {
        handlePlayerBottomObstacleCollision(window, dt); //gravity

        handlePlayerRightObstacleCollision(window, dt);

        handlePlayerLeftObstacleCollision(window, dt);

        handlePlayerTopObstacleCollision(window, dt); //jumping

        handlePlayerShootLogic(window, dt);
    }

    std::string update(sf::RenderWindow& window, float dt, std::string& level) {
        nextLevel = level;

        handleCoinLogic();

        handleBulletLogic(window, dt);

        handlePlayerLogic(window, dt);

        handleEnemyLogic(window, dt);

        return nextLevel; 
    }

    void drawTo(sf::RenderWindow& window) {
        for(int i = 0; i < coinVec.size(); i++) {
            coinVec.at(i)->drawTo(window);
        }

        for(int i = 0; i < bulletVec.size(); i++) {
            bulletVec.at(i)->drawTo(window);
        }

        for(int i = 0; i < obstacleVec.size(); i++) {
            window.draw(obstacleVec.at(i)->getShape());
        }

        for(int i = 0; i < enemyVec.size(); i++) {
            enemyVec.at(i)->drawTo(window);
        }

        window.draw(createText(window, "Score: " + std::to_string(score), 20, player.getX(), 20, sf::Color::Red));
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
