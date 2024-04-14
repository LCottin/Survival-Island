#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "Player.hpp"
#include "Screen.hpp"
#include "NPC.hpp"
#include "Board.hpp"
#include "GamePub.hpp"

using namespace std;
using namespace sf;

class Game
{
    private:
        shared_ptr<Player>                  _Player;
        shared_ptr<Board>                   _Board;
        shared_ptr<Screen>                  _Screen;
        shared_ptr<vector<shared_ptr<NPC>>> _NPCs;

        Vector2u   _BoardSizeInPixel;
        GameStatus _GameStatus;

        void _ResetSharedEvent(sharedEvents &sharedEvent);
        void _HandleEvents(sharedEvents &sharedEvent);
        void _MovePlayer(const sharedEvents &sharedEvent);
        void _MoveNPCs();
        void _HandleInteractions();
        void _Draw();
        bool _AreClose(const Player &player, const NPC &npc, const uint32_t threshold) const;

    public:
        Game(const string &playerName);

        void play();

        ~Game();
};

#endif
