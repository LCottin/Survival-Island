#ifndef __SCREEN_DATA_HPP__
#define __SCREEN_DATA_HPP__

#include <iostream>

constexpr uint32_t IMAGE_WIDTH_PIXEL  = 256U;
constexpr uint32_t IMAGE_HEIGHT_PIXEL = 224U;

constexpr float_t CHANGE_DIRECTION_THRESHOLD = 0.6f;

constexpr uint32_t INFO_PANEL_WIDTH_PIXEL = 120U;

enum class GameStatus : uint32_t
{
    INIT,
    PLAY,
    PAUSE,
    STOP,
};

#endif //__SCREEN_DATA_HPP__
