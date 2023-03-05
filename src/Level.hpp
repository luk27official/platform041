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

/**
 * @brief A class that represents a game level
*/
class Level {
    int score = 0;

    //clocks for cooldowns
    sf::Clock jumpClock;
    sf::Clock shootClock;
    //level timer
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
    /**
     * @brief A method called when the player dies. Resets the enemies, coins and the player
    */
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

    /**
     * @brief A method that parses the "ground" type of element from the json file
    */
    void parseGround(const json& data) {
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

    /**
     * @brief A method that parses the "wall", "killzone" and "finish" types of element from the json file
    */
    void parseWall(const json& data, const WallType type) {
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

    /**
     * @brief A method that parses the "enemy" type of element from the json file
    */
    void parseEnemy(const json& data) {
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

    /**
     * @brief A method that parses the "coin" type of element from the json file
    */
    void parseCoin(const json& data) {
        float x = data["x"];
        float y = data["y"];

        std::shared_ptr<Coin> coin = std::make_shared<Coin>();

        coin->setPos({ x, y + player.getHeight() });
        coinVec.push_back(coin);
    }

    /**
     * @brief A method that parses the json file, calls the appropriate methods for each element
    */
    void parseJson(const std::string& path) {
        std::string actualPath = "res/" + path + ".json";

        std::ifstream f(actualPath);
        json data = json::parse(f);

        for(auto& element : data) {
            std::string e = element["type"];
            //remove the quotes from the string
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

    /*
    * @brief A constructor that loads the font and calls the parseJson method
    */
    Level(const std::string& path) {
        //here we could possibly do something else when the font fails to load, but it does not really affect the functionality of the game
        //(the game will still run, but the menu text will not be displayed) 
        if (!font.loadFromFile("res/vermin_vibes.ttf"))
        {
            std::cerr << "Error loading font" << std::endl;
        }

        parseJson(path);
    }

    /**
     * @brief A method that is called when the player wins the level. Displays a message and waits for 3 seconds before returning to the menu
    */
    void gameWin(sf::RenderWindow &window) {
        window.setView(sf::View(sf::Vector2f(0, Constants::get_window_height() / 2.0), sf::Vector2f(Constants::get_window_width(), Constants::get_window_height())));
        
        std::string displayText = "You win! Score: " + std::to_string(score) + ", Time (s): " + std::to_string(levelClock.getElapsedTime().asSeconds());
        sf::Text text = createText(window, displayText, 50, 0, 300, sf::Color(0, 155, 0));

        sf::Clock clock;

        nextLevel = "menu";

        while(clock.getElapsedTime().asSeconds() < 3) {
            //using active waiting - could be potentially changed to a more elegant solution
            //i.e using multiple threads
            window.clear(sf::Color::White);
            window.draw(text);
            sleep(sf::milliseconds(100));
            window.display();
        }
    }

    /*
    * @brief A method that is called when creating a new text object. Used for the score and the post-game stats
    */
    sf::Text createText(sf::RenderWindow &window, const std::string& displayText, int size, int x, int y, const sf::Color color = sf::Color::Black) {
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

    /**
     * @brief Checks if the player is colliding with any of the obstacles on the bottom. Based on the obstacle type, the player either dies, wins or just collides
    */
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

        //gravity
        if(!colliding) {
            //the condition is used to prevent the player from falling through the ground
            if (player.getY() < Constants::get_window_height() - 100 && player.isJumping == false) {
                player.move({ 0, player.gravity * dt });
            }
        }
    }

    /**
     * @brief Checks if the player is colliding with any of the obstacles on the right when moving. Based on the obstacle type, the player either dies, wins or just collides
    */
    void handlePlayerRightObstacleCollision(sf::RenderWindow& window, float dt) {
        if (player.isMovingRight) {
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
            //the if condition just prevents the player from moving outside the level
            if(!colliding && player.getX() < ground.getGlobalBounds().width - player.getWidth()) {
                player.move({ player.moveSpeed * dt, 0 });
                window.setView(sf::View(sf::Vector2f(player.getX(), Constants::get_window_height() / 2.0), sf::Vector2f(Constants::get_window_width(), Constants::get_window_height())));
            }
        }
    }

    /**
     * @brief Checks if the player is colliding with any of the obstacles on the right when moving. Based on the obstacle type, the player either dies, wins or just collides
    */
    void handlePlayerLeftObstacleCollision(sf::RenderWindow& window, float dt) {
        if (player.isMovingLeft) {
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
                window.setView(sf::View(sf::Vector2f(player.getX(), Constants::get_window_height() / 2.0), sf::Vector2f(Constants::get_window_width(), Constants::get_window_height())));
            }
        }
    }

    /**
     * @brief Checks if the player is colliding with any of the obstacles on the top when moving. Based on the obstacle type, the player either dies, wins or just collides
    */
    void handlePlayerTopObstacleCollision(sf::RenderWindow& window, float dt) {
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

            //jump logic
            if(jumpClock.getElapsedTime().asSeconds() > player.resetJumpTime) {
                player.isJumping = false;
                jumpClock.restart();
            }

            if(!colliding && player.getY() > 0) {
                player.move({ 0, -player.moveSpeed * dt });
            }
        }
    }

    /*
    * @brief Handles the logic of the player shooting
    */
    void handlePlayerShootLogic(sf::RenderWindow& window, float dt) {
        if (player.isShooting) {
            std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>();
            float bulletX = player.getX();

            //to make sure the bullet is not inside the player
            if(player.direction == Direction::Right) {
                bulletX += player.getWidth();
            }
            else {
                bulletX -= player.getWidth();
            }

            bullet->setPos({ bulletX, (float)(player.getY() + player.getHeight() / 2) });
            bullet->direction = player.direction;
            bulletVec.push_back(bullet);

            player.isShooting = false;
        }
    }

    /*
    * @brief Handles the logic of the enemy collisions (works the same as the player collisions)
    */
    void handleEnemyObstacleCollision(const std::shared_ptr<Enemy>& e, float dt) {
        // bottom collision
        bool colliding = false;
        for (int i = 0; i < obstacleVec.size(); i++) {
            sf::RectangleShape o = obstacleVec.at(i)->getShape();
            if (e->bottomObstacleCollision(o)) {
                colliding = true;
                break;
            }
        }

        //gravity
        if(!colliding) {
            if (e->getY() < (Constants::get_window_height() - 100) - e->getGlobalBounds().height + player.getHeight()) {
                e->move({ 0, e->gravity * dt });
            }
        }

        //check left collision
        if(e->direction == Direction::Left) {
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
        //check right collision
        else if (e->direction == Direction::Right) {
            bool colliding = false;
            for (int i = 0; i < obstacleVec.size(); i++) {
                sf::RectangleShape o = obstacleVec.at(i)->getShape();
                if (e->rightObstacleCollision(o)) {
                    colliding = true;
                    break;
                }
            }
            if(!colliding && e->getX() < ground.getGlobalBounds().width - e->getGlobalBounds().width) {
                e->move({ e->moveSpeed * dt, 0 });
            }
            else {
                e->direction = Direction::Left;
            }
        }

    }

    /*
    * @brief Handles the logic of the enemy (collision with obstacles, collision with player)
    */
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

    /*
    * @brief Handles the logic of the coins (collision with player)
    */
    void handleCoinLogic() {
        for (int i = 0; i < coinVec.size(); i++) {
            std::shared_ptr<Coin> c = coinVec.at(i);
            if(c->isCollected) {
                continue;
            }
            
            if (player.isCollidingWithCoin(c)) {
                c->isCollected = true;
                score++;
            }
        }
    }

    /*
    * @brief Handles the logic of the bullets (collision with enemies, collision with obstacles)
    */
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

            if (b->getX() > ground.getGlobalBounds().width || b->getX() < 0) {
                bulletVec.erase(bulletVec.begin() + i);
            }
        }
    }

    /*
    * @brief Calls all the functions that handle the logic of the player
    */
    void handlePlayerLogic(sf::RenderWindow& window, float dt) {
        handlePlayerBottomObstacleCollision(window, dt); //gravity

        handlePlayerRightObstacleCollision(window, dt);

        handlePlayerLeftObstacleCollision(window, dt);

        handlePlayerTopObstacleCollision(window, dt); //jumping

        handlePlayerShootLogic(window, dt);
    }

    /*
    * @brief Handles the general logic of the game
    */
    void update(sf::RenderWindow& window, float dt) {
        handleCoinLogic();

        handleBulletLogic(window, dt);

        handlePlayerLogic(window, dt);

        handleEnemyLogic(window, dt);
    }

    /*
    * @brief Draws all the objects to the window
    */
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

    /*
    * @brief Handles the events of the game
    */
    std::string handleEvents(sf::Event& event, sf::Window& window, const std::string& level) {
        nextLevel = level;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {
                    window.close();
                    break;
                }

                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Up) {
                        if(!player.isJumping) {
                            if(jumpClock.getElapsedTime().asSeconds() > player.resetJumpTime) {
                                player.isJumping = true;
                                jumpClock.restart();
                            }
                        }
                    }
                    else if(event.key.code == sf::Keyboard::Space) {
                        if(!player.isShooting) {
                            if(shootClock.getElapsedTime().asSeconds() > player.resetShootTime) {
                                player.isShooting = true;
                                shootClock.restart();
                            }
                        }
                    }
                    else if(event.key.code == sf::Keyboard::Left) {
                        player.isMovingLeft = true;
                    }
                    else if(event.key.code == sf::Keyboard::Right) {
                        player.isMovingRight = true;
                    }
                    else if(event.key.code == sf::Keyboard::Escape) {
                        nextLevel = "menu";
                    }
                    break;
    
                case sf::Event::KeyReleased:
                    if(event.key.code == sf::Keyboard::Up) {
                        player.isJumping = false;
                    }
                    else if(event.key.code == sf::Keyboard::Space) {
                        player.isShooting = false;
                    }
                    else if(event.key.code == sf::Keyboard::Left) {
                        player.isMovingLeft = false;
                    }
                    else if(event.key.code == sf::Keyboard::Right) {
                        player.isMovingRight = false;
                    }
                    break;
                
                default:
                    break;
            }
        }
        return nextLevel;
    }
};
