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
        Player         *_Player;
        Board          *_Board;
        Screen         *_Screen;
        vector<shared_ptr<NPC>>  *_NPCs;

    public:
        Game(const string &playerName);

        void play();

        ~Game();
};

#endif
