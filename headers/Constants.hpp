#pragma once

/*
* @brief A class that contains constants that are used throughout the game (in our case just the window size)
*/
class Constants {
    static inline const float WINDOW_WIDTH = 1000;
    static inline const float WINDOW_HEIGHT = 600;

public:
    /*
    * @brief Returns the specified window width
    */
    static inline float get_window_width() {
        return WINDOW_WIDTH;
    };

    /*
    * @brief Returns the specified window height
    */
    static inline float get_window_height() {
        return WINDOW_HEIGHT;
    };
};