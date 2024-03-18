#ifndef __MINIMAP_HPP__
#define __MINIMAP_HPP__

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Board.hpp"
#include "Player.hpp"

using namespace std;
using namespace sf;

class Minimap
{
    private:
        uint32_t _WidthInPixel;
        uint32_t _HeightInPixel;
        Vector2u _Position;
        View     _View;

    public:
        Minimap(const uint32_t widthInPixel, const uint32_t heightInPixel, const Vector2u &position, const RenderWindow &window);

        const View& getView()           const;
        uint32_t    getWidthInPixel()   const;
        uint32_t    getHeightInPixel()  const;

        void update(const Board &board, const Player &player);
};

#endif
