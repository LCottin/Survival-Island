#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <iostream>

#include "ServerNetwork.hpp"

class Game
{
    private:
        unique_ptr<ServerNetwork> _ServerNetwork;

    public:
        Game();
        Game(const string& configName);

        void play();
};

#endif
