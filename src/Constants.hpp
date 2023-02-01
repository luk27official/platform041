#pragma once

class Constants {
    static inline const float WINDOW_WIDTH = 1000;
    static inline const float WINDOW_HEIGHT = 600;

public:
    static inline float get_window_width() {
        return WINDOW_WIDTH;
    };
    static inline float get_window_height() {
        return WINDOW_HEIGHT;
    };
};