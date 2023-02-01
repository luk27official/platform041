# Platform041
A singleplayer 2D platform game. Inspired by many 2D platformers like Mario, the player controls a stickman which needs to make their way to the finish as fast as possible (with as many points as possible).

## Game overview
- simple 2D platform game written in C++
- uses [SFML](https://github.com/SFML/SFML.git) library for 2D graphics and [nlohmann_json](https://github.com/nlohmann/json.git) library for parsing JSON configuration files
- contains multiple levels
- a level consists of a world (defined in a JSON configuration file) containing some obstacles, collectibles and enemies
- player's goal is to move the character to the end of the level without dying to enemies and killing obstacles
- player may collect coins which will define the end score, they are not required to collect them though
- each level contains a timer which may be either a time limit, or simply a part of their own personal statistics
- future optional extensions: personal statistics, level statistics, new levels, new types of enemies, ...

For more details, see the `docs` folder.
