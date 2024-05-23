#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "Player.hpp"
#include "Screen.hpp"
#include "NPC.hpp"
#include "Board.hpp"
#include "ClientNetwork.hpp"

using namespace std;
using namespace sf;

class Game
{
    private:
        shared_ptr<Player>                  _Player;
        shared_ptr<Board>                   _Board;
        shared_ptr<Screen>                  _Screen;
        shared_ptr<vector<shared_ptr<NPC>>> _NPCs;

        unique_ptr<ClientNetwork> _ClientNetwork;

        GameStatus     _GameStatus;
        inputEvents    _InputEvents;
        outputCommands _OutputCommands;

        void _WaitForStatus();
        void _SynchronizeToServer() const;
        void _SynchronizeFromServer();
        void _ResetInputEvent();
        void _CatchEvents();
        void _UpdateGame();
        void _Draw() const;

    public:
        Game(const string &playerName, const string &configName);

        void play();

        ~Game();
};

#endif
