# Platform041
A singleplayer 2D platform game. Inspired by many 2D platformers like Mario, the player controls a stickman which needs to make their way to the finish as fast as possible (with as many points as possible).

To move the player, use the arrow keys. To select an option in the menu and to shoot, use the spacebar.

## Build requirements
- CMake 3.21 or newer
- C++ compiler (recommended: gcc)

This project uses the CMake tool to compile all of the necessary libraries and source code. To compile, just run the CMake tool via CLI. It is also possible to run the included scripts - `build.cmd` for Windows (with MinGW installed) or `build.sh` for Linux. After building, the executable is located in the `build` folder. Just run `build/Platform041.exe` or the respective equivalent for other operating systems.

Warning (Debian/WSL users): CMake compiles the SFML and JSON library from scratch. For that, you may need to download those packages (although already included in most systems) - `sudo apt-get install libpthread-stubs0-dev libgl1-mesa-dev libx11-dev libxrandr-dev libfreetype6-dev libglew-dev libjpeg8-dev libsndfile1-dev libopenal-dev libxcursor-dev libudev-dev libflac-dev libvorbis-dev`

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
