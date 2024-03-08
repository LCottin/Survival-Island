#ifndef __WINDOWVIEW_HPP__
#define __WINDOWVIEW_HPP__

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Board.hpp"
#include "Player.hpp"

using namespace std;
using namespace sf;

class WindowView
{
    private:
        uint32_t  _WidthInPixel;
        uint32_t  _HeightInPixel;
        View      _View;

    public:
        WindowView();

        View&    getView();
        uint32_t getWidthInPixel() const;
        uint32_t getHeightInPixel() const;
        Vector2u getPosition() const;
        Vector2u getCenterPosition() const;

        void update(const Board &board, const Player &player);
};

#endif
