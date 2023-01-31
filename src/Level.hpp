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
    float levelWidth = 4000; //defined by the json

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

    void die(sf::RenderWindow& window) {
        score = 0;

        for(int i = 0; i < enemyVec.size(); i++) {
            enemyVec.at(i)->isAlive = true;
        }

        for(int i = 0; i < coinVec.size(); i++) {
            coinVec.at(i)->isCollected = false;
        }

        player.die(window);
    }

    void parseGround(json& data) {
        float width = data["width"];
        float height = data["height"];

        float x = data["x"];
        float y = data["y"];
        
        int r = data["color"]["r"];
        int g = data["color"]["g"];
        int b = data["color"]["b"];

        ground.setSize({ width, height });
        ground.setFillColor(sf::Color(r, g, b));
        ground.setPosition({ x, y + player.getHeight() });
    }

    void parseWall(json& data, WallType type) {
        float width = data["width"];
        float height = data["height"];

        float x = data["x"];
        float y = data["y"];

        std::shared_ptr<CustomWall> obstacle;

        switch (type)
        {
        case WallType::ClassicWall:
            obstacle = std::make_shared<ClassicWall>();
            break;
        case WallType::KillingObstacle:
            obstacle = std::make_shared<KillingObstacle>();
            break;
        case WallType::Finish:
            obstacle = std::make_shared<Finish>();
            break;        
        default:
            break;
        }

        obstacle->setSize({ width, height });
        obstacle->setPos({ x, y + player.getHeight() });

        obstacleVec.push_back(obstacle);
    }

    void parseEnemy(json& data) {
        //enemy size is determined by the texture size
        float x = data["x"];
        float y = data["y"];

        int gravity = data["gravity"];
        int speed = data["speed"];

        std::string texturePath = data["texturePath"];

        std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(gravity, speed, texturePath);
    
        enemy->setPos({ x, y + player.getHeight() });
        enemyVec.push_back(enemy);
    }

    void parseCoin(json& data) {
        float x = data["x"];
        float y = data["y"];

        std::shared_ptr<Coin> coin = std::make_shared<Coin>();

        coin->setPos({ x, y + player.getHeight() });
        coinVec.push_back(coin);
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
            } else if(e == "wall") {
                parseWall(element, WallType::ClassicWall);
            } else if(e == "killzone") {
                parseWall(element, WallType::KillingObstacle);
            } else if(e == "finish") {
                parseWall(element, WallType::Finish);
            } else if(e == "coin") {
                parseCoin(element);
            } else if(e == "enemy") {
                parseEnemy(element);
            }
        }

    }

    Level(std::string& path) {
        if (!font.loadFromFile("res/vermin_vibes.ttf"))
        {
            std::cout << "Error loading font" << std::endl;
        }

        parseJson(path);
    }

    void gameWin(sf::RenderWindow &window) {
        std::cout << "You win!" << std::endl;

        window.setView(sf::View(sf::Vector2f(0, 300), sf::Vector2f(1000, 600)));
        std::string displayText = "You win! Score: " + std::to_string(score) + ", Time (s): " + std::to_string(levelClock.getElapsedTime().asSeconds());
        sf::Text text = createText(window, displayText, 50, 0, 300, sf::Color(0, 155, 0));

        sf::Clock clock;

        nextLevel = "menu";

        while(clock.getElapsedTime().asSeconds() < 3) {
            window.clear(sf::Color::White);
            window.draw(text);
            sleep(sf::milliseconds(100));
            window.display();
        }

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
                        die(window);
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
            player.flipSprite();
            bool colliding = false;
            for (int i = 0; i < obstacleVec.size(); i++) {
                sf::RectangleShape o = obstacleVec.at(i)->getShape();
                if (player.rightObstacleCollision(o)) {
                    switch(obstacleVec.at(i)->type) {
                        case WallType::ClassicWall:
                            colliding = true;
                            break;
                        case WallType::KillingObstacle:
                            die(window);
                            break;
                        case WallType::Finish:
                            gameWin(window);
                            break;
                    }
                    break;
                }
            }
            if(!colliding && player.getX() < levelWidth - player.getWidth()) {
                player.move({ player.moveSpeed * dt, 0 });
                window.setView(sf::View(sf::Vector2f(player.getX(), 300), sf::Vector2f(1000, 600)));
            }
        }
    }

    void handlePlayerLeftObstacleCollision(sf::RenderWindow& window, float dt) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player.direction = Direction::Left;
            player.flipSprite();
            bool colliding = false;
            for (int i = 0; i < obstacleVec.size(); i++) {
                sf::RectangleShape o = obstacleVec.at(i)->getShape();
                if (player.leftObstacleCollision(o)) {
                    switch(obstacleVec.at(i)->type) {
                        case WallType::ClassicWall:
                            colliding = true;
                            break;
                        case WallType::KillingObstacle:
                            die(window);
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
                            die(window);
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
                float bulletX = player.getX();
                if(player.direction == Direction::Right) {
                    bulletX += player.getWidth();
                }
                else {
                    bulletX -= player.getWidth();
                }
                bullet->setPos({ bulletX, (float)(player.getY() + player.getHeight() / 2) });
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
            if (e->getY() < groundHeight - e->getGlobalBounds().height + player.getHeight()) {
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

            if(!e->isAlive) {
                continue;
            }

            if (player.isCollidingWithEnemy(e)) {
                die(window);
                break;
            }
        }
    }

    void handleCoinLogic() {
        for (int i = 0; i < coinVec.size(); i++) {
            std::shared_ptr<Coin> c = coinVec.at(i);
            if(c->isCollected) {
                continue;
            }
            
            if (player.isCollidingWithCoin(c)) {
                c->isCollected = true;
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
                if(!e->isAlive) {
                    continue;
                }

                if (b->isCollidingWithEnemy(e)) {
                    e->isAlive = false; 
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

    void handleEscape() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            nextLevel = "menu";
        }
    }

    std::string update(sf::RenderWindow& window, float dt, std::string& level) {
        nextLevel = level;

        handleEscape();

        handleCoinLogic();

        handleBulletLogic(window, dt);

        handlePlayerLogic(window, dt);

        handleEnemyLogic(window, dt);

        return nextLevel; 
    }

    void drawTo(sf::RenderWindow& window) {
        for(int i = 0; i < coinVec.size(); i++) {
            if(!coinVec.at(i)->isCollected) {
                coinVec.at(i)->drawTo(window);
            }
        }

        for(int i = 0; i < bulletVec.size(); i++) {
            bulletVec.at(i)->drawTo(window);
        }

        for(int i = 0; i < obstacleVec.size(); i++) {
            window.draw(obstacleVec.at(i)->getShape());
        }

        for(int i = 0; i < enemyVec.size(); i++) {
            if(enemyVec.at(i)->isAlive) {
                enemyVec.at(i)->drawTo(window);
            }
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
