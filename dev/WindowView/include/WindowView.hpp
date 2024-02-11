#ifndef __WINDOWVIEW_HPP__
#define __WINDOWVIEW_HPP__

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Board.hpp"
#include "Player.hpp"
#include "ConfigDev.hpp"
#include "WindowViewData.hpp"

using namespace std;
using namespace sf;

class WindowView
{
    private:
        uint32_t  _WidthInPixel;
        uint32_t  _HeightInPixel;
        uint32_t  _SizeInPixel;
        View      _View;
        Board    &_Board;
        Player   &_Player;

    public:
        WindowView(Board &board, Player &player);

        View&    getView();
        Vector2f getViewSize() const;
        uint32_t getWidthInPixel() const;
        uint32_t getHeightInPixel() const;
        uint32_t getSizeInPixel() const;
        Vector2f getPosition() const;
        Vector2f getCenterPosition() const;

        void     update();
};

#endif
