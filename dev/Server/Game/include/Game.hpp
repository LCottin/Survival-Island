#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <iostream>

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

        void _sendInitData();

    public:
        Game(const string& configName);

        void play();
};

#endif
