#pragma once

#include "SFML/Graphics.hpp"

#include <fstream>
#include "nlohmann/json.hpp"
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

    std::vector<std::unique_ptr<Coin>> coinVec;
    std::vector<std::unique_ptr<CustomWall>> obstacleVec;
    std::vector<std::unique_ptr<Enemy>> enemyVec;
    std::vector<std::unique_ptr<Bullet>> bulletVec;
    std::vector<sf::Text> textVec;

    sf::Font font;

    std::string nextLevel;

public:
    /**
     * @brief A method called when the player dies. Resets the enemies, coins and the player
    */
    void die(sf::RenderWindow& window);

    /**
     * @brief A method that parses the "ground" type of element from the json file
    */
    void parseGround(const json& data);

    /**
     * @brief A method that parses the "wall", "killzone" and "finish" types of element from the json file
    */
    void parseWall(const json& data, const WallType type);

    /**
     * @brief A method that parses the "enemy" type of element from the json file
    */
    void parseEnemy(const json& data);

    /**
     * @brief A method that parses the "coin" type of element from the json file
    */
    void parseCoin(const json& data);

    /**
     * @brief A method that parses the json file, calls the appropriate methods for each element
    */
    void parseJson(const std::string& path);

    /*
    * @brief A constructor that loads the font and calls the parseJson method
    */
    explicit Level(const std::string& path);

    /**
     * @brief A method that is called when the player wins the level. Displays a message and waits for 3 seconds before returning to the menu
    */
    void gameWin(sf::RenderWindow &window);

    /*
    * @brief A method that is called when creating a new text object. Used for the score and the post-game stats
    */
    sf::Text createText(sf::RenderWindow &window, const std::string& displayText, int size, int x, int y, const sf::Color color = sf::Color::Black);

    /**
     * @brief Checks if the player is colliding with any of the obstacles on the bottom. Based on the obstacle type, the player either dies, wins or just collides
    */
    void handlePlayerBottomObstacleCollision(sf::RenderWindow& window, float dt);

    /**
     * @brief Checks if the player is colliding with any of the obstacles on the right when moving. Based on the obstacle type, the player either dies, wins or just collides
    */
    void handlePlayerRightObstacleCollision(sf::RenderWindow& window, float dt);

    /**
     * @brief Checks if the player is colliding with any of the obstacles on the right when moving. Based on the obstacle type, the player either dies, wins or just collides
    */
    void handlePlayerLeftObstacleCollision(sf::RenderWindow& window, float dt);

    /**
     * @brief Checks if the player is colliding with any of the obstacles on the top when moving. Based on the obstacle type, the player either dies, wins or just collides
    */
    void handlePlayerTopObstacleCollision(sf::RenderWindow& window, float dt);

    /*
    * @brief Handles the logic of the player shooting
    */
    void handlePlayerShootLogic(sf::RenderWindow& window, float dt);

    /*
    * @brief Handles the logic of the enemy collisions (works the same as the player collisions)
    */
    void handleEnemyObstacleCollision(Enemy* e, float dt);

    /*
    * @brief Handles the logic of the enemy (collision with obstacles, collision with player)
    */
    void handleEnemyLogic(sf::RenderWindow& window, float dt);

    /*
    * @brief Handles the logic of the coins (collision with player)
    */
    void handleCoinLogic();

    /*
    * @brief Handles the logic of the bullets (collision with enemies, collision with obstacles)
    */
    void handleBulletLogic(sf::RenderWindow& window, float dt);

    /*
    * @brief Calls all the functions that handle the logic of the player
    */
    void handlePlayerLogic(sf::RenderWindow& window, float dt);

    /*
    * @brief Handles the general logic of the game
    */
    void update(sf::RenderWindow& window, float dt);

    /*
    * @brief Draws all the objects to the window
    */
    void drawTo(sf::RenderWindow& window);

    /*
    * @brief Handles the events of the game
    */
    std::string handleEvents(sf::Event& event, sf::Window& window, const std::string& level);
};
