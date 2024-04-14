#ifndef __GAME_PUB_HPP__
#define __GAME_PUB_HPP__

#include <iostream>

enum class GameStatus : uint32_t
{
    INIT,
    PLAY,
    PAUSE,
    STOP,
};

typedef struct
{
    bool isGamePaused;
    bool movePlayerUp;
    bool movePlayerDown;
    bool movePlayerLeft;
    bool movePlayerRight;
} sharedEvents;

#endif //__GAME_PUB_HPP__
