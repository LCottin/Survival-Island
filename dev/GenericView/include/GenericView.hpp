#ifndef __GENERICVIEW_HPP__
#define __GENERICVIEW_HPP__

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Board.hpp"
#include "Player.hpp"

using namespace std;
using namespace sf;

class GenericView
{
    private:
        uint32_t _WidthInPixel;
        uint32_t _HeightInPixel;
        uint32_t _LimitOffsetInPixel;
        Vector2u _Position;
        View     _View;

    public:
        GenericView(const uint32_t widthInPixel, const uint32_t heightInPixel, const Vector2u &position, const RenderWindow &window, const uint32_t limitOffsetInPixel = 0, const float_t zoomFactor = 1.0f);

        const View& getView()          const;

        void update(const Board &board, const Player &player);
};

#endif
