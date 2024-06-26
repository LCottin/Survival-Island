#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <iostream>
#include <thread>

#include "ServerNetwork.hpp"
#include "Player.hpp"
#include "NPC.hpp"
#include "Board.hpp"

class Game
{
    private:
        unique_ptr<ServerNetwork>           _ServerNetwork;

        shared_ptr<Board>                   _Board;
        shared_ptr<Player>                  _Player;
        shared_ptr<vector<shared_ptr<NPC>>> _NPCs;

        Vector2u       _BoardSizeInPixel;
        GameStatus     _GameStatus;
        inputEvents    _InputEvents;
        outputCommands _OutputCommands;

        thread _Shutdown;

        void _UpdateOutputCommands();
        void _sendInitData();
        void _waitForPlayer();
        void _SynchronizeToClient();
        void _SynchronizeFromClient();
        void _MovePlayer();
        void _MoveNPCs();
        void _HandleInteractions();

        void _HandleShutdown();

    public:
        Game(const string& configName);

        void play();

        ~Game();
};

#endif
