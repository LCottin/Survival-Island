#ifndef __BOARDVIEW_HPP__
#define __BOARDVIEW_HPP__

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Board.hpp"
#include "Player.hpp"

using namespace std;
using namespace sf;

class BoardView
{
    private:
        uint32_t _WidthInPixel;
        uint32_t _HeightInPixel;
        uint32_t _LimitOffsetInPixel;
        Vector2u _Position;
        View     _View;

    public:
        BoardView(const uint32_t widthInPixel, const uint32_t heightInPixel, const uint32_t limitOffsetInPixel, const Vector2u &position);

        const View& getView()           const;
        uint32_t    getWidthInPixel()   const;
        uint32_t    getHeightInPixel()  const;

        void update(const Board &board, const Player &player);
};

#endif
