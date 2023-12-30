#ifndef __SCREEN_HPP__
#define __SCREEN_HPP__

#include <iostream>
#include <string>
#include <memory>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Board.hpp"
#include "Player.hpp"
#include "NPC.hpp"
#include "ScreenData.hpp"

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

        Board                   &_Board;
        Player                  &_Player;
        vector<shared_ptr<NPC>>  _NPCs;

        mt19937 _Random;

        void _computeVertices();
        void _drawBoard();
        void _drawPlayer();
        void _drawNPCs();
        void _drawIndicators();
        void _HandleEvents();

    public:
        Screen(Board &board, Player &player, const string title = "Empty title");

        uint32_t getWidthPixel() const;
        uint32_t getHeightPixel() const;
        uint32_t getSizePixel() const;

        void setWindowTitle(const string title);
        void setBoard(Board &board);

        void render();
        void addNPC(shared_ptr<NPC> &NPC);

        ~Screen();
};


#endif
