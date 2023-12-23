#ifndef __SCREEN_HPP__
#define __SCREEN_HPP__

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Board.hpp"
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

        Board       &_Board;

        void _computeVertices();
        void _draw();

    public:
        Screen(Board &board, const string title = "Empty title");

        uint32_t getWidthPixel() const;
        uint32_t getHeightPixel() const;
        uint32_t getSizePixel() const;

        void setWindowTitle(const string title);
        void setBoard(Board &board);

        void render();

        ~Screen();
};


#endif
