#ifndef __SCREEN_HPP__
#define __SCREEN_HPP__

#include <iostream>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Board.hpp"
#include "Player.hpp"
#include "NPC.hpp"
#include "ScreenData.hpp"
#include "Random.hpp"

#include "ConfigDev.hpp"
#include "ConfigUser.hpp"

using namespace std;
using namespace sf;

class Screen
{
    private:
        RenderWindow _Window;
        Vector2u     _TileSize;
        Texture      _TilesetTexture;
        VertexArray  _Vertices;

        uint32_t     _WidthPixel;
        uint32_t     _HeightPixel;
        uint32_t     _SizePixel;
        string       _WindowTitle;
        GameStatus   _GameStatus;

        Board                   &_Board;
        Player                  &_Player;
        vector<shared_ptr<NPC>>  _NPCs;

        Clock _PauseCooldown;
        Time  _PauseTimer;

        void _computeVertices();
        void _drawBoard();
        void _drawPlayer();
        void _drawNPCs();
        void _drawIndicators();
        void _HandleEvents();
        void _HandleInteractions();

    public:
        Screen(Board &board, Player &player, const string &title);

        uint32_t getWidthPixel()  const;
        uint32_t getHeightPixel() const;
        uint32_t getSizePixel()   const;

        void setWindowTitle(const string &title);
        void setBoard(Board &board);

        void render();
        void addNPC(shared_ptr<NPC> &NPC);
        bool areClose(Player &player, NPC &npc, const uint32_t threshold) const;

        ~Screen();
};


#endif
