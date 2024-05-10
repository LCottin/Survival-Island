#ifndef __TYPES_HPP__
#define __TYPES_HPP__

#include <iostream>
#include <SFML/Network.hpp>

using namespace std;
using namespace sf;

enum class GameStatus : uint32_t
{
    INIT,
    WAITING,
    READY,
    PLAY,
    PAUSE,
    STOP,
};

typedef struct
{
    bool     isAlive;
    uint32_t health;
    bool     hasMoved;
    Vector2f position;
} characterCommand;

struct inputEvents
{
    bool isGamePaused;
    bool movePlayerUp;
    bool movePlayerDown;
    bool movePlayerLeft;
    bool movePlayerRight;

    void serialize(Packet &packet) const;
    void deserialize(Packet &packet);
};

struct outputCommands
{
    GameStatus               gameStatus;
    characterCommand         playerCommand;
    vector<characterCommand> NPCsCommands;

    void serialize(Packet &packet) const;
    void deserialize(Packet &packet);
};

#endif
