# Platform041 documentation

## User documentation
- TODO

## Programming documentation

The program uses the [SFML](https://github.com/SFML/SFML.git) library for 2D graphics. For the levels the program uses the [nlohmann_json](https://github.com/nlohmann/json.git) library. The program uses the C++17 standard.

The main logic of the window is controlled by the `Controller` class. The class decides what to draw based on a string with the specified menu/level. The controller also calls all the methods for event handling and game updates.

The `Menu` class contains everything for the menu. When a new level is added to the game, this class has to be modified as well.

The `Level` class contains the biggest part of the game logic. At first, the instance is created when changing the level from the main menu. Then, the corresponding JSON file is loaded from the `res` folder. Currently, the naming should follow this convention: The name of the JSON file is the same as the menu label (but in lowercase and without whitespace). So, the menu label "Level 3" would get renamed to level3, which results to the `res/level3.json` file.

The JSON file is basically just an array of objects. There are multiple types of objects which can be parsed by the program. 2 examples follow:

```json
{
    "type": "wall",
    "width": 300,
    "height": 100,
    "x": 200,
    "y": 500
}
```

This JSON object creates a wall with the width of 300 and height 100 at the x of 200 and y 500 + player height. All of the objects are moved down by the player height on the y axis.

```json
{
    "type": "enemy",
    "x": 700,
    "y": 300,
    "gravity": 800,
    "speed": 100,
    "texturePath": "res/enemy.png"
}
```

This JSON object creates a walkable enemy with the gravity of 800 and speed of 100 at x 700 and y 300 + player height. The enemy's size is determined by the texture size which is specified by the texturePath property.

There are more types which may be parsed by the program such as "finish", "coin" or "killzone". For explicit parameters of those types refer to the `Level` class. This format allows us to add new types of obstacles/enemies pretty easily. The only requirement is to add the required methods for parsing the JSON data to the `Level` class and make sure that everything is drawn to the screen properly. The parsing methods create instances of the corresponding classes such as `ClassicWall`, `Finish`, `Enemy` etc.

The last class to mention is the `Player` class. It contains needed methods for detecting various collisions. The `Enemy` class is similar to this one.

There are some extensions which could be added to the game:
- Overall game statistics
- Level statistics
- More levels
- More enemies (shooting ones, standing ones etc.)
- More guns, collectibles
- Unlockables, player levelling etc.

Basically, there are a lot of options to extend the game.

Overall, it was pretty hard to set up all the libraries and files to work. Starting with SFML is not really that easy. On the other side, once the programmer understands the basics of SFML, it is not hard to extend the game and add new features. It is basically harder to think of the level design and game innovations than to add new features.