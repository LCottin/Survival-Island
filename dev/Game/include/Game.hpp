#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "Player.hpp"
#include "Screen.hpp"
#include "NPC.hpp"
#include "Board.hpp"

using namespace std;
using namespace sf;

class Game
{
    private:
        shared_ptr<Player>                  _Player;
        shared_ptr<Board>                   _Board;
        shared_ptr<Screen>                  _Screen;
        shared_ptr<vector<shared_ptr<NPC>>> _NPCs;

    public:
        Game(const string &playerName);

        void play();

        ~Game();
};

#endif
