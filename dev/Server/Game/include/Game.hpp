#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <iostream>

#include "ServerNetwork.hpp"
#include "Player.hpp"
#include "NPC.hpp"

class Game
{
    private:
        unique_ptr<ServerNetwork>           _ServerNetwork;
        shared_ptr<Player>                  _Player;
        shared_ptr<vector<shared_ptr<NPC>>> _NPCs;

    public:
        Game();
        Game(const string& configName);

        void play();
};

#endif
